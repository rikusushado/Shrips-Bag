// config_structure.rs

/*****************************/
/* JSON STRUCTURE DEFINITION */
/*****************************/

/*************************/
/* Please edit mindfully */
/*************************/

use utils::rukky_types;
use utils::Deserialize;

#[derive(Debug, Deserialize)]
pub struct Initializer {
    pub global: String,
    pub zulip: String,
    pub language: String,
}

#[derive(Debug, Deserialize)]
pub struct Global {
    pub time_format: char,
    pub lang_select: String,
    pub usage_trigger: u8,
}

#[derive(Debug, Deserialize)]
pub struct Zulip {
    pub url: String,
    pub key: String,
    pub email: String,
    pub stream : String,
    pub topic : String,
}

#[derive(Debug, Deserialize)]
pub struct Language {
    pub dictionary: rukky_types::StrMap,
}

#[derive(Debug, Deserialize)]
pub struct Target {
    pub dictionary: rukky_types::VecMap,
}

#[derive(Debug, Deserialize)]
pub struct ConfigFile {
    pub global: Global,
    pub zulip: Zulip,
    pub target: Target,
    pub language: Language,
}

// Shrips Bag project protected under GNU GPL v3.0 License
// Developed by Rikusu Shado
