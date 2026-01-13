# Loggirus 

**Loggirus** - custom logging library written in C++. 

Loggirus comes from `Logging` and `Papirus`. While subject to change, it is the first name that wasn't taken.

## Why?

Loggirus will match some distinct requirements. Besides learning purposes, the purpose of `Loggirus` is to be a fun logging library that could be used in pet projects.

Format is subject to change.

Terminal should support UTF-8 to display the icons properly.

## Code examples

```cpp
domeeno::Log logger(domeeno::Level::DEBUG);

logger.info("output of logging, [{}] [{}]!", "Hello", "World");
logger.debug("operating system: {}", getOsName());
logger.error("{} feature is not working ", "random phrases");
logger.warn("test number {}", 42);

```

Outputs:
```
🛠️ [2026/01/13 18:39] [INFO] output of logging, [Hello] [World]!  - maybe it is time to sleep.
ℹ️ [2026/01/13 18:39] [DEBUG] operating system: Linux  - algebraic, CS degree.
⚠️ [2026/01/13 18:39] [ERROR] random phrases feature is not working   - would you like to play some Baldur's Gate?
💢 [2026/01/13 18:39] [WARN] test number 42  - hmm a warning? probably nothing.

```

Changing the logger level will change logs capture:

```cpp

// domeeno::Log logger(domeeno::Level::DEBUG);
domeeno::Log logger(domeeno::Level::INFO);

// same logs
```

Outputs:

```
⚠️ [2026/01/13 18:33] [ERROR] random phrases feature is not working   - oh nooo.
💢 [2026/01/13 18:33] [WARN] test number 42  - should we worry about this?
```


## WIP

- [x] Add time/date in the prepend.
- [ ] Add file and line location calling the log. (how am I going to do this? 🫨)
- [ ] Add thread calling the log. (how am I going to do this? 🫨)
- [x] Implement logging on a peer thread.
- [x] Make sure it doesn't interfere with cout of main app. (how am I going to do this? 🫨).
    - answer: don't use multiple `<<` operators, they might be interleaved. Use a single `<<` operator per log line.
- [x] Implement ThreadSafeQueue DS.
- [x] Add debug, warn, error methods.
- [ ] Improve randomness thing (doesn't work currently).
- [x] Make repo public.
- [ ] Test impl in the field.
- [x] Add screenshots/examples of the result.

