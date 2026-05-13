// shrip_argument.rs

mod shrip_parse;

use std:fs;
use std::collections::HashMap;

/***************************/
/* SHRIP ARGUMENT HANDLER */
/***************************/

trait Methods {
    fn read_config_file(&self, file_path: String, bundled: bool);

    fn check_cli_arguments(&self, valid_arguments: String);
}

struct Argument {
    is_config_bundled: bool;
    config_file_path: String;
}

impl Methods for Argument {
    fn read_config_file(&self, file_path: String, bundled: bool) -> String {
        let config_data: &'static str = if bundled {
            include_str!(file_path);
        } else {
            let config_data = fs::read_to_string(file_path);    
        }

        return config_data;
    }

    fn check_cli_arguments(valid_arguments: String) -> String {
        let argv: Vec<String> = env::args().collect();
        let argc: i16 = argv.len();

        let validv: Vec<String> = valid_arguments.to_vec();
        let validc: i16 = validv.len();

        arg_pair_map = HashMap::new();

        for i in 0..argc {
            if i == 0 && i % 2 != 0 {
                continue;
            }
            
            let arg: String = &argv[i];

            for c in 0..validc {
                let valid: String = &validv[&c];
                
                if arg == valid {
                    index: i16 = &c + 1;
                    value: String = &argv[index];

                    arg_pair_map.insert(arg, value); 
                    
                    break;
                }
            }
        }

        return arg_pair_map; 
    }
}
