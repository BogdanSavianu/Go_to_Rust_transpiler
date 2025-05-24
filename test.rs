use std::io;
fn do_something(c: i32) -> i32 {
    let mut a = 10;
    let mut b = a + 5;
    if 2 < 10 {
        b = b + 3;
    } else {
        b = b - 3;
    }
    while b < 30 {
        b = b + 1;
    }
    for i in 0.. a {
        b = b + i;
    if i % 2 == 0 {
        b = b * 2;
    }
}
    return b;
}
fn main() {
}
