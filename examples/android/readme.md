## NasNas Android example

This folder contains an example gradle project (inspired by SFML android example). 
You can compile it either by using the command line or by using Android Studio.

### Requirements

Before compiling this example, you have to build and install SFML and NasNas for Android using the Android NDK.

Android NDK version "20.1.5948944" must be installed from the Android Studio SDK manager.

To build and install SFML for Android : 

```bash
git clone https://github.com/SFML/SFML && cd SFML
mkdir build-android && cd build-android
cmake -DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=/path/to/AndroidSDK/ndk/20.1.5948944 -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a -DCMAKE_ANDROID_STL_TYPE=c++_static -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -j4
cmake --install .
```

To build and install NasNas for Android, it is the same process :

```bash
git clone https://github.com/Madour/NasNas && cd NasNas
mkdir build-android && cd build-android
cmake -DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=/path/to/AndroidSDK/ndk/20.1.5948944 -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a -DCMAKE_ANDROID_STL_TYPE=c++_static -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -j4
cmake --install .
```

If everything worked, you should have a `sfml` and a `nasnas` directories in your NDK's `sources/third_party` folder.

### Build the example using command line

Follow these steps to compile the apk :

- Create a `local.properties` file inside this folder. 
Specify the location of your Android SDK installation like this :
```
sdk.dir=/path/to/AndroidSdk 
```

- Make sure you have Java JDK 11 installed on your computer.
- Run : `./gradlew build`

And you're done !

To run the application on your smartphone, plug your device and enable USB debugging in "Settings > Developer Options".

Then run : `./gradlew installDebug"`. The application will be installed, tap on the icon to run it.


### Build the example with Android Studio

Start Android Studio and open the folder as a project. The IDE will automatically detect the gradle project
and synchronize the settings (can take a while).

Once it is done, make sure your device is plugged with Developer Options enabled, then press the Run button to run 
the application on your smartphone.

### Troubleshooting

If you get the following error message when building : 

```
Error: Android Gradle plugin requires Java 11 to run. You are currently using Java 1.8.'
```

Find the `.gradle` folder in your user directory (`~/.gradle` or `C:/Users/UserName/.gradle`) and create a
`gradle.properties` file inside. Specify your Java JDK 11 installation path in the `org.gradle.java.home` variable like this :

```
# Example path for Linux
org.gradle.java.home=/usr/lib/jvm/java-11-openjdk
```