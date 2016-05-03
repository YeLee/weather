#ifndef USERDEF_HPP
#define USERDEF_HPP

#ifndef USE_STRUCT
#define USE_STRUCT
#endif

struct LangInfo_t {
    const char * fullName;
    const char * shortName;
};

LangInfo_t WeatherLanguage[] {
    { "English",    "en" },
    { "Russian",    "ru" },
    { "Italian",    "it" },
    { "Spanish",    "es" },
    { "Ukrainian",  "uk" },
    { "German",     "de" },
    { "Portuguese", "pt" },
    { "Romanian",   "ro" },
    { "Polish",     "pl" },
    { "Finnish",    "fi" },
    { "Dutch",      "nl" },
    { "French",     "fr" },
    { "Bulgarian",  "bg" },
    { "Swedish",    "sv" },
    { "Chinese Traditional", "zh_tw" },
    { "Chinese Simplified", "zh_cn" },
    { "Turkish",    "tr" },
    { "Croatian",   "hr" },
    { "Catalan",    "ca" }
};

struct TemperatureUnit_t
{
    const char * name;
    const char * shortName;
};

TemperatureUnit_t TemperatureType[] {
    { "Fahrenheit", "imperial" },
    { "Celsius",    "metric" },
    { "Kelvin",     "" }
};

#endif // USERDEF_HPP
