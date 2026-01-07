# Loggirus 

**Loggirus** - custom logging library written in C++. 

Loggirus comes from `Logging` and `Papirus`. While subject to change, it is the first name that wasn't taken.

## Why?

Loggirus will match some distinct requirements. Besides learning purposes, the purpose of `Loggirus` is to be a fun logging library that could be used in pet projects.

A logged line could look like this:

```
🌿 [2024-06-01 12:00:00] [🌿 info: so far so good] [utils.cpp:42] result 42.
🍁 [2024-06-01 12:00:00] [🍁 debug: you might want to know...] [utils.cpp:42] result 42.
🍂 [2024-06-01 12:00:00] [🍂 error: uh oh...] [utils.cpp:42] result 42.
```

Format is subject to change.

Terminal should support UTF-8 to display the icons properly.

## WIP

- [ ] Read prepend/append log messages from a file.
- [ ] Add time/date in the prepend.
- [ ] Add file and line location calling the log. (how am I going to do this? 🫨)
- [ ] Add thread calling the log. (how am I going to do this? 🫨)
- [ ] Implement logging on a peer thread.
- [x] Implement ThreadSafeQueue DS.
- [x] Add debug, warn, error methods.
- [ ] Make repo public.
- [ ] Test impl in the field.
- [ ] Add screenshots of the result.

