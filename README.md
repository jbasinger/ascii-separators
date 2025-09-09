# Ascii Separators!

If you check out [ASCII codes](https://www.asciitable.com/) 28-31, you'll see that they are data separators.  
Why do we use characters we need to escape and write a bunch of special code around instead of using these?  
CSV? Tabs? `|`s?! Any writable character is annoying and needs to be escaped.  
  
These ascii codes are seem to be purpose-built separators that won't require escaping, because you don't type them!

I made typedefs to add the name of `group` to `table`, `record` to `row` and `unit` to `field` so I can keep a mental model of a database. The originals are still defined as their first names as well.

This is just a little repo to test out playing with them. I plan on it being unit tested, and have functions to
save the data to a file, load files back up and print it legibly somehow.

## How to build and test it

If you have docker, you can run `./cli.sh` and it will give you a shell in the build environment.  
Then just run `./test.sh` to test and/or `./build.sh` to build the regular `main.c` that does nothing right now.  
`./test.sh` is much more interesting, so check out `test/main.c` to see the meat and potatoes for now.

If you want to run it out of docker, you just need the typical gcc compiler, I think. Whatever you get from
the `build-essential` package in ubuntu. Then you can just go into the `src/` dir and run the test and build scripts from there.

## Can I use your beautiful library outside of here?

Of course and thank you, I'm so flattered! When things are built, a shared library `lib/libsep.so` will show up and you're free to use it in another project. To see how it's done, check out the build and test scripts. It is linked for tests and the main program.