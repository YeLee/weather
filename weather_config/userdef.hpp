#ifndef USERDEF_HPP
#define USERDEF_HPP

const int LangCount = 19;
const char *WeatherLanguage[LangCount][2] {
    { "English", "en" },
    { "Russian", "ru" },
    { "Italian", "it" },
    { "Spanish", "es" },
    { "Ukrainian", "uk" },
    { "German", "de" },
    { "Portuguese", "pt" },
    { "Romanian", "ro" },
    { "Polish", "pl" },
    { "Finnish", "fi" },
    { "Dutch", "nl" },
    { "French", "fr" },
    { "Bulgarian", "bg" },
    { "Swedish", "sv" },
    { "Chinese Traditional", "zh_tw" },
    { "Chinese Simplified", "zh_cn" },
    { "Turkish", "tr" },
    { "Croatian", "hr" },
    { "Catalan", "ca" }
};

const int TempTypeCount = 3;
const char *TemperatureType[TempTypeCount][2] {
    { "Fahrenheit", "imperial" },
    { "Celsius", "metric" },
    { "Kelvin", "" }
};

#endif // USERDEF_HPP
