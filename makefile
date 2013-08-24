install all:
        sudo cc play.c -o /usr/bin/play
        sudo chown root:users /usr/bin/play
        sudo chmod +rxs /usr/bin/play
        sudo cp disable-discrete-gpu.conf /usr/lib/tmpfiles.d/

uninstall clean:
        sudo rm /usr/bin/play
        sudo rm /usr/lib/tmpfiles.d/disable-discrete-gpu.conf
