// Shrips Bag project protected under GNU GPL v3.0 License
// Developed by Rikusu Shado

// This is a SECURE STRING HASHMAP to avoid panic by user missconfig

#![allow(dead_code)]

use std::collections::hash_map::{IntoIter, Iter, IterMut};
use std::any::TypeId;

pub use std::collections::HashMap;

fn is_strmap<T: 'static>(_variable: &T) -> bool {
    TypeId::of::<T>() == TypeId::of::<HashMap<String, String>>()
}
pub struct StrMap(HashMap<String, String>);
impl StrMap {
    fn new(h: HashMap<String, String>) -> Option<Self> {
        if is_strmap(&h) {
            Some(StrMap(h))
        } else {
            None
        }
    }
}
impl StrMap {
    pub fn get(&self, key: &str) -> Option<&String> {
        self.0.get(key)
    }

    pub fn get_mut(&mut self, key: &str) -> Option<&mut String> {
        self.0.get_mut(key)
    }
}
impl IntoIterator for StrMap {
    type Item = (String, String);
    type IntoIter = IntoIter<String, String>;

    fn into_iter(self) -> Self::IntoIter {
        self.0.into_iter()
    }
}
impl<'a> IntoIterator for &'a StrMap {
    type Item = (&'a String, &'a String);
    type IntoIter = Iter<'a, String, String>;

    fn into_iter(self) -> Self::IntoIter {
        self.0.iter()
    }
}
impl<'a> IntoIterator for &'a mut StrMap {
    type Item = (&'a String, &'a mut String);
    type IntoIter = IterMut<'a, String, String>;

    fn into_iter(self) -> Self::IntoIter {
        self.0.iter_mut()
    }
}