## NasNas Android example

This folder contains an example gradle project (inspired by SFML android example). 
You can compile it either by using command line or by using Android Studio. 

### Command line

Follow these steps to compile the apk :

- Create a `local.properties` file inside this folder. 
Specify the location of your Android SDK installation like this :
```
# Example path for Linux
sdk.dir=/home/UserName/path/to/Android/Sdk 
# OR
# Example path for Windows
sdk.dir=C:/Android
```

- Make sure you have Java JDK 11 installed on your computer.
- Run : `./gradlew build`

And you're done !

To run the application on your smartphone, plug your device and enable USB debugging in "Settings > Developer Options".

Then run : `./gradlew installDebug"`. The application will be installed, tap on the icon to run it.


### Android Studio

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