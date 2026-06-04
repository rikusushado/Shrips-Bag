// main.rs

/**************************/
/* MAIN SOURCE APP SOURCE */
/**************************/

/*************************/
/* Please edit mindfully */
/*************************/

#[path = "./config_structure.rs"] mod data_struct;

use utils::{File, BufReader, HashMap};
use std::{process::Command};
use std::io::Read;
use serde_json;
use std::process;

use std::net::TcpStream;
use std::path::Path;
use ssh2::{Session};
use ssh2;

fn execute_remote(address: &str, port: &u16, key_path: &str,
    user: &str, command: &str, outstream: &mut String)   -> Result<(), Box<dyn std::error::Error>> {
        println!("{}:{}", address, port);
        let tcp = TcpStream::connect(format!("{}:{}", address, port))?;

        let mut sess = Session::new()?;
        sess.set_tcp_stream(tcp);
        sess.handshake()?;

        let path_expanded = shellexpand::tilde(key_path).into_owned();
        let path = Path::new(&path_expanded);

        println!("{}", path_expanded);

        sess.userauth_pubkey_file(
            user,
            None,
            Path::new(path),
                                None,
        )?;

        if !sess.authenticated() {
            return Err("Error: Could not be authenticated with private key".into());
        }

        let mut channel = sess.channel_session()?;

        sess.set_blocking(true);

        channel.exec(command)?;

        channel.read_to_string(outstream)?;

        channel.wait_close()?;

        Ok(())
}

fn read_file(path: &str) -> String {
    let path = shellexpand::tilde(path).into_owned();
    let file = File::open(&path).unwrap_or_else(|error| {
        eprintln!("{}", error);
        eprintln!("Please, ensure the following path exists: {}", path);
        process::exit(0x0100);
    });

    let mut reader = BufReader::new(file);

    let mut content = String::new();
    reader.read_to_string(&mut content).unwrap();
    content
}

fn filter_percentage(input: String) -> String {
    let mut numbers: Vec<char> = Vec::new();
    let mut count: u8 = 0;

    for c in input.chars() {
        if count == 3 {
            count -= 1;
            numbers.drain(..1);
        }
        if c == '%' && count > 0 {
            break;
        }
        if c.is_numeric() {
            count += 1;
            numbers.push(c);
        } else {
            count = 0;
            numbers.clear();
        }
    }

    let digit: String = numbers.into_iter().collect();
    let pcent: String = format!("{}", digit);
    return pcent
}

fn load_config() -> data_struct::ConfigFile {
    let init_path = "/opt/shrips-bag/config/disk-usage/init.json";
    let init_file = &read_file(&init_path);
    let initf: data_struct::Initializer = serde_json::from_str(&init_file)
        .expect("error while reading or parsing");

    let global_path = initf.global;
    let global_file = &read_file(&global_path);
    let globalf: data_struct::Global = serde_json::from_str(&global_file)
        .expect("error while reading or parsing");

    let zulip_path = initf.zulip;
    let zulip_file = &read_file(&zulip_path);
    let zulipf: data_struct::Zulip = serde_json::from_str(&zulip_file)
        .expect("error while reading or parsing");

    let target_path = "~/.shrips/disk_usage/target.json";
    let target_file = &read_file(&target_path);
    let targetf: data_struct::Target = serde_json::from_str(&target_file)
        .expect("error while reading or parsing");

    let language_path = initf.language;
    let language_file = read_file(&language_path);
    let languagef: data_struct::Language = serde_json::from_str(&language_file)
    .expect("error while reading or parsing");

    let config_file = data_struct::ConfigFile {
        global: globalf,
        zulip: zulipf,
        target: targetf,
        language: languagef,
    };

    return config_file;
}

fn read_usage(target: &data_struct::Target, trigger: &u8, high: &mut bool) -> HashMap<String, String> {
    let read_command = "df --output=pcent /";

    let mut name_command = HashMap::new();
    let mut name_usage: HashMap<String, String> = HashMap::new();
    
    for (key, array) in &target.dictionary {
        if array.len() < 4 { continue; }

        let address  = array[0].to_string();
        let port     = array[1].to_string();
        let key_path = array[2].to_string();
        let user     = array[3].to_string();
        let command  = read_command.to_string();

        let cmd = vec![address, port, key_path, user, command];

        name_command.insert(key.clone(), cmd);
    }

    for (key, cmd) in &name_command {
        let mut output = String::new();

        let _ = execute_remote(&cmd[0], &cmd[1].parse::<u16>().unwrap(), &cmd[2], &cmd[3], &cmd[4], &mut output);

        let pcent: String = filter_percentage(output);

        if let Ok(lookup_value) = pcent.parse::<u8>() {
            if lookup_value >= *trigger {
                name_usage.insert(key.clone(), pcent);
                *high = true;
            }
        }
    }
    return name_usage;
}

fn get_date(format: char) -> String{
    let utc = chrono::offset::Utc::now();
    let time = &utc.to_string();

    let year: &str = &time[..4];
    let month: &str= &time[5..7];
    let day = &time[8..10];

    let mut date = String::from("");
    match format {
        'm' => date.push_str(&format!("{day}/{month}/{year}")),
        'i' => date.push_str(&format!("{month}/{day}/{year}")),
        _ =>  println!("Unkown date format!"),
    }

    return date;
}
fn language_handle<'a>(lang: &'a data_struct::Language, selection: &String) -> &'a str {
    lang.dictionary.get(selection).unwrap()
}

fn build_message(name_usage: HashMap<String, String>, header: &str, format: char) -> String {
    let mut message = String::new();

    message.push_str(&format!("{}", header));

    for (name, usage) in name_usage {
        message.push_str(&format!("| {} | `{}%` |\n", name, usage));
    }

    message.push_str("\n---\n");
    let date = get_date(format);
    message.push_str(&format!("### ***{}***", date));
    message.push_str("\n---");

    return message.to_string();
}

fn send_message(zulip: &data_struct::Zulip, message: &String) {

    println!("{}", message);

    let output = Command::new("curl")
        .arg("--insecure")
        .arg("-X")
        .arg("POST")
        .arg(&zulip.url)
        .arg("-u")
        .arg(format!("{}:{}", zulip.email, zulip.key))
        .arg("--data-urlencode")
        .arg("type=stream")
        .arg("--data-urlencode")
        .arg(format!("to={}", zulip.stream))
        .arg("--data-urlencode")
        .arg(format!("topic={}", zulip.topic))
        .arg("--data-urlencode")
        .arg(format!("content={}", message))
        .output()
    .expect("Message sending error");



    if output.status.success() {
        println!("✅ Message sended succesfully!");
    } else {
        eprintln!("❌ Error: {}", String::from_utf8_lossy(&output.stderr));
    }
}

fn main() {
    let config = load_config();
    let mut high = false;
    let name_usage = read_usage(&config.target, &config.global.usage_trigger, &mut high);

    if !high {
        println!("No storage usage is over the {}% treshold.", config.global.usage_trigger);
        return
    }

    let selection = &config.global.lang_select;
    let lang_path = language_handle(&config.language , selection);

    let header = read_file(&lang_path);

    let format = config.global.time_format;

    let message = build_message(name_usage, &header, format).to_string();

    let zulip_config = &config.zulip;
    send_message(zulip_config, &message);
}

// Shrips Bag project protected under GNU GPL v3.0 License
// Developed by Rikusu Shado
