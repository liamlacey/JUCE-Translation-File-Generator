# JUCE Translation File Generator #

JUCE Translation File Generator is a simple GUI application for generating suitable translation files for use with the [JUCE](http://www.rawmaterialsoftware.com/juce.php) Library and its [LocalisedStrings](http://www.rawmaterialsoftware.com/api/classLocalisedStrings.html) class. 

The application scans through your projects source code (through a directory or a single file) for instances of the TRANS("") macro or translate("") function, extracts the String within the quotes that needs translating, and adds them to a correctly formatted LocalisedStrings translation file that is all ready to have translations added. It also allows Strings to be added to existing translation files without adding duplicates of strings already within the file.

## Requirements ##
Non.

## License ##

JUCE Translation File Generator is licensed under the GPLv2. See GPL2.txt for details.

It uses the [JUCE](http://www.rawmaterialsoftware.com/juce.php) library which is licensed under the GPLv2. 
