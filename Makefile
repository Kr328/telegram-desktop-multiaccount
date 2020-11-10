libtghook.so: hook.cpp
	gcc -fPIC hook.cpp -o libtghook.so -I/usr/include/qt -I/usr/include/qt/QtCore -lQt5Core -shared

.PHONY: build
build: libtghook.so

.PHONY: install
install: build
	install -m 700 -d -D ${HOME}/.local/lib
	install -m 600 libtghook.so ${HOME}/.local/lib/libtghook.so
	install -m 700 -D -d ${HOME}/.local/share/TelegramDesktopFork
	install -m 600 -D telegramdesktopfork.desktop ${HOME}/.local/share/applications/telegramdesktopfork.desktop