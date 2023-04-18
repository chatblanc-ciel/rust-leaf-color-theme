extern crate regex;
extern crate thiserror;

use std::collections::HashMap;
use thiserror::Error as ThisError;

#[derive(Debug, ThisError)]
enum MyError {
    #[error("include same key({0}).")]
    IncludeSameKey(String),
}

/// # What do
///
/// extract from string
///
/// ```
/// let txt = String::from("foofoobarfoofoofoobar");
/// let extract = do_samething(&txt);
/// println!("{:?}", extract)
/// ```
fn do_something<'a>(has_lifetime: &'a str) -> Result<HashMap<&'a str, &'a str>, MyError> {
    use regex::Regex;

    let mut list = HashMap::new();

    // set Regular experssion
    let re = Regex::new(r"export (?P<key>[\w]+)=(?P<value>[\S]+)(\n||\r\n)*").unwrap();

    for capture in re.captures_iter(file_data) {
        /*
          Should change it.
          Maybe key&value style hashmap is not good.
        */
        if list.contains_key(&capture["key"]) {
            return Err(Box::new(MyError::IncludeSameKey(
                capture["key"].to_string(),
            )));
        } else {
            list.insert(capture["key"], capture["value"]);
        }
    }
    Ok(env_list)
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let has_lifetime = HasLifetime {
        some_string: "example",
    };
    do_something(&has_lifetime);
    Ok(())
}
