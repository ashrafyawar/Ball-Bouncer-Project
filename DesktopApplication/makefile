all: build_desktop

build_desktop:
	cd ball_bouncer && ./qmake ball_bouncer.pro
	+$(MAKE) -C ball_bouncer
	mv ball_bouncer/ball_bouncer ../BBDesktop
	chmod +x ../BBDesktop

clean:
	cd ball_bouncer && $(MAKE) clean
	rm -f ../BBDesktop
	rm -f ball_bouncer/qmake
