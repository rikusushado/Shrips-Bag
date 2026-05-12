// shrip_argument.rs

use std:fs;

/***************************/
/* SHRIP ARGUMENT HANDLER */
/***************************/

trait Methods {
    fn read_config_file(&self, file_path: String, bundled: bool);
}

struct Argument {
    is_config_bundled: bool;
    config_file_path: String;
}

impl Methods for Argument {
    fn read_config_file(&self, file_path: String, bundled: bool) {
        let config_data: &'static str = if bundled {
            include_str!(file_path);
        } else {
            let config_data = fs::read_to_string(file_path);    
        }

        return config_data;
    }
}
