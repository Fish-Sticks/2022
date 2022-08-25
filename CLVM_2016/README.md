# CLVM_2016
# Roblox CLVM for a 2016 client, I programmed everything in here from scratch.
# I programmed for 14 hours straight lets go, it was very fun.

Things to note:
Anything before mid 2019 is using the old Roblox VM, which basically means it's just a lua5.1.4 (or 5.1.5?) VM which is full of encryptions on shit like OP_CALL, OP_CLOSURE, other opcodes, idk

I made a CLVM because I couldn't find the deserializer lmao, and I didn't wanna deal with the encryptions while doing proto conversion.

I reversed around for like 3 hours and spent 3 hours programming, had a working CLVM at hour 6.

I'll update this to have error handling in L->errfunc so you don't just shit game when a lua exception gets thrown, it crashes right now because of trying to create a new thread.

![](https://i.gyazo.com/81147b516b120d3dbeda1f73565f2ea6.gif)
