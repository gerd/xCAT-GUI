xcatgui: FormLogin.cpp Main.cpp client_http.hpp  client_https.hpp
	#g++ FormLogin.cpp Main.cpp `wx-config-3.0 --libs --cxxflags` -o xcatgui -std=c++11 -O3 -Wall   -rdynamic -lboost_regex -lboost_system -lboost_thread -lboost_coroutine -lboost_context -lssl -lcrypto
	g++ FormLogin.cpp Main.cpp `wx-config-3.0 --libs --cxxflags` -o xcatgui -std=c++17 -lssl -lcrypto -lboost_system
clean:
	rm -f xcatgui
