
add: install

install:
	g++ 																				\
	-fPIC 																				\
	view.cpp moc_view.cpp openGL.cpp 													\
	../controller/controller.cpp 														\
	../model/*.cpp																	\
	-I/usr/include/x86_64-linux-gnu/qt6 												\
	-I/usr/include/x86_64-linux-gnu/qt6/QtWidgets 										\
	-I/usr/include/x86_64-linux-gnu/qt6/QtOpenGL 										\
	-I/usr/include/x86_64-linux-gnu/qt6/QtOpenGLWidgets									\
	-I/usr/include/x86_64-linux-gnu/qt6/QtGui											\
	-lQt6Widgets -lQt6Core -lQt6OpenGL -lOpenGL -lQt6OpenGLWidgets -lQt6Gui -o My_model			\