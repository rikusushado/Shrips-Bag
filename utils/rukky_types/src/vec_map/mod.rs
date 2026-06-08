// Shrips Bag project protected under GNU GPL v3.0 License
// Developed by Rikusu Shado

// This is a SECURE VECTOR HASHMAP to avoid panic by user missconfig

#![allow(dead_code)]

use std::collections::hash_map::{IntoIter, Iter, IterMut};
use std::any::TypeId;

pub use std::collections::HashMap;

fn is_vecmap<T: 'static>(_variable: &T) -> bool {
    TypeId::of::<T>() == TypeId::of::<HashMap<String, Vec<String>>>()
}
pub struct VecMap(HashMap<String, Vec<String>>);
impl VecMap {
    fn new(h: HashMap<String, Vec<String>>) -> Option<Self> {
        if is_vecmap(&h) {
            Some(VecMap(h))
        } else {
            None
        }
    }
}
impl VecMap {
    pub fn get(&self, key: &str) -> Option<&Vec<String>> {
        self.0.get(key)
    }

    pub fn get_mut(&mut self, key: &str) -> Option<&mut Vec<String>> {
        self.0.get_mut(key)
    }
}
impl IntoIterator for VecMap {
    type Item = (String, Vec<String>);
    type IntoIter = IntoIter<String, Vec<String>>;

    fn into_iter(self) -> Self::IntoIter {
        self.0.into_iter()
    }
}
impl<'a> IntoIterator for &'a VecMap {
    type Item = (&'a String, &'a Vec<String>);
    type IntoIter = Iter<'a, String, Vec<String>>;

    fn into_iter(self) -> Self::IntoIter {
        self.0.iter()
    }
}
impl<'a> IntoIterator for &'a mut VecMap {
    type Item = (&'a String, &'a mut Vec<String>);
    type IntoIter = IterMut<'a, String, Vec<String>>;

    fn into_iter(self) -> Self::IntoIter {
        self.0.iter_mut()
    }
}