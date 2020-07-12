/**
* Created by Modar Nasser on 15/04/2020.
**/


#pragma once


namespace ns {
    // forward declaration of App type
    class App;

    /** AppComponent
     * Allows any class to access App properties
     */
    class AppComponent {
    public:
        static App* app;
    };

}
