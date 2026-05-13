// shrip_parse.rs

/***********************/
/* SHRIP PARSER MODULE */
/***********************/

// Common configuration file formats
struct ini {
}

impl ini {
    fn parse_helper(&self, text: String, is_header: bool) -> String {
        if is_header {
            let length: i32 = text.len();
            let header: String;

            for i in 0..length {
                
            }
        }
    }
    fn indent_handler(&self, text: String) -> bool 
    fn parse_handler(&self, text: String) -> HashMap {
    }
}

struct json {
}

struct toml {
}
