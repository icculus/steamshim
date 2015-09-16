What is this?

This is a small piece of code, written in C++, that acts as a bridge between
a child process and the Steamworks SDK. The child process links against a
small piece of code, written in C, to facilitate communication with the
bridge.

What would I ever need this for?

There are two good reasons to use this piece of code:

- You have a GPL-licensed game and can't link directly against the Steamworks
SDK. The child process links against the simple, open source C code, which
talks to the open source C++ code via a pipe, which talks to Steamworks. You
can now add Steam achievements to your game without violating the GPL.

- You have a game written in a programming language that can't interact with
C++ directly, so you can't make use of the Steamworks SDK directly. If your
language can link to C-callable code, you can use this to wire up to
Steamworks.


How does it work?

- The parent process (the C++ code) gets launched as if it were your game. It
initializes Steamworks, creates some pipes and launches your actual game, then
waits on your game to talk to it over those pipes.

- Your game links against steamshim_child.c and at some point #includes
steamshim_child.h to use this functionality.

- Your game calls STEAMSHIM_init() at startup to prepare the system. It can
then make other STEAMSHIM_*() calls to interact with the parent process and
Steamworks.

- Your game, once a frame, calls STEAMSHIM_pump() until it returns NULL. Each
time it doesn't return NULL is a new message (event) from the parent process.
Often times, this is results from a command you asked the parent process to
do earlier, or some other out-of-band event from Steamworks.

- Your game, when shutting down normally, calls STEAMSHIM_deinit(), so the
parent process knows you're going away. It says goodbye, shuts down the pipe,
waits for your game to terminate, and then terminates itself.


Is this all of Steamworks?

- No! It's actually just enough to deal with stats and achievements right now,
but it can definitely be extended to offer more things. Take a look at


Is there an example?

That would be testapp.c. This example expects you to own Postal 1 on Steam and
will RESET ALL YOUR ACHIEVEMENTS, so be careful running it. But hey, if you
lose your work, it's a good exercise in SteamShim usage to put them back
again.  :)

Questions? Ask me.

--ryan.
icculus@icculus.org


