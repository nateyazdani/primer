primer
======

A nifty little tool to automate hybrid graphics under Linux (using the open-source drivers &amp; systemd)

        In and of itself primer does very little; all it does is make utilizing the leading hybrid GPU switching
technology under Linux (PRIME) much easier.  This ONLY works when both GPUs are running the open-source drivers.  This is
because the proprietary ones don't implement support for PRIME/DMA-BUF (though NVIDIA is trying to add it to theirs.).
After primer is installed, your discrete GPU will be automatically powered down after boot in order to save power.  If you
wish to run a graphically-intensive program, just prefix it with 'play' on the command line, which will turn the GPU on
before your program starts and then turn it back off afterwards.  I recommend only ever having one instance of 'play'
runnig at a time (otherwise whichever one closes first will probably crash any others).  Running a 'play sh' to spawn
other processes ought to be fine though.  Although DRI PRIME (the real technology behind all this) isn't considered very
robust/stable, this setup is working just fine for me (Intel Core i5, 2012 & Radeon 6850M, muxless).
