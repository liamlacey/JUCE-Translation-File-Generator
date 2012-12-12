/*
 *  AppComponent.cpp
 *  TranslationFileGenerator
 *
 *  Created by Liam Lacey on 9/08/2012.
 *  Copyright 2012.
 *
 */

//  This file is part of TranslationFileGenerator.
//
//  TranslationFileGenerator is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License, version 2, 
//  as published by the Free Software Foundation.
//  
//  TranslationFileGenerator is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "AppComponent.h"

AppComponent::AppComponent() : Thread ("generatorThread")
{
    //======translate file controls============
    addAndMakeVisible(newFileButton = new TextButton("Create New File"));
    newFileButton->addListener(this);
    newFileButton->setClickingTogglesState(true);
    newFileButton->setRadioGroupId(1);
    newFileButton->setConnectedEdges(2);
    newFileButton->setToggleState(true, false);

    addAndMakeVisible(editFileButton = new TextButton("Add To Existing File"));
    editFileButton->addListener(this);
    editFileButton->setClickingTogglesState(true);
    editFileButton->setRadioGroupId(1);
    editFileButton->setConnectedEdges(1);
    
    //new file stiff
    fileDirectory = new FilenameComponent ("file directory",
                                           File::getSpecialLocation(File::userDocumentsDirectory),
                                           false, true, false,
                                           String::empty,
                                           String::empty,
                                           "Choose Directory for File");
    fileDirectory->addListener (this);					
	fileDirectory->setMaxNumberOfRecentFiles(10);
	addAndMakeVisible (fileDirectory);
    
    addAndMakeVisible(fileNameEditor = new TextEditor());
    fileNameEditor->setMultiLine(false);
    fileNameEditor->setReturnKeyStartsNewLine(false);
    fileNameEditor->addListener(this);
    fileNameEditor->setText("new_trans_file", false);
    
    addAndMakeVisible(languageEditor = new TextEditor());
    languageEditor->setMultiLine(false);
    languageEditor->setReturnKeyStartsNewLine(false);
    languageEditor->addListener(this);
    languageEditor->setTextToShowWhenEmpty("Enter language...", Colours::grey);
    
    addAndMakeVisible(countriesEditor = new TextEditor());
    countriesEditor->setMultiLine(false);
    countriesEditor->setReturnKeyStartsNewLine(false);
    countriesEditor->addListener(this);
    countriesEditor->setTextToShowWhenEmpty("Enter country codes...", Colours::grey);
    
    //existing file stuff
    fileLocation = new FilenameComponent ("file location",
                                           File::nonexistent,
                                           false, false, false,
                                           String::empty,
                                           String::empty,
                                           "Choose translation file");
    fileLocation->addListener (this);					
	fileLocation->setMaxNumberOfRecentFiles(10);
    addChildComponent(fileLocation);
    
    
    //====== searching controls=====
    addAndMakeVisible(searchDirectoryButton = new TextButton("Search Directory"));
    searchDirectoryButton->addListener(this);
    searchDirectoryButton->setClickingTogglesState(true);
    searchDirectoryButton->setRadioGroupId(2);
    searchDirectoryButton->setConnectedEdges(2);
    searchDirectoryButton->setToggleState(true, false);
    
    addAndMakeVisible(searchFileButton = new TextButton("Search Single File"));
    searchFileButton->addListener(this);
    searchFileButton->setClickingTogglesState(true);
    searchFileButton->setRadioGroupId(2);
    searchFileButton->setConnectedEdges(1);
    
    //search directory controls
    directoryToSearch = new FilenameComponent ("directory to search",
                                               File::nonexistent,
                                               false, true, false,
                                               String::empty,
                                               String::empty,
                                               "Choose directory to search");
    directoryToSearch->addListener (this);					
	directoryToSearch->setMaxNumberOfRecentFiles(10);
    addAndMakeVisible (directoryToSearch);
    
    addAndMakeVisible (fileTypeGroup = new GroupComponent ("group", "File types to search..."));
    addAndMakeVisible (cppTypeButton = new ToggleButton (".ccp"));
    cppTypeButton->addListener(this);
    cppTypeButton->setToggleState(true, false);
    addAndMakeVisible (hTypeButton = new ToggleButton (".h"));
    hTypeButton->addListener(this);
    hTypeButton->setToggleState(true, false);
    addAndMakeVisible (cTypeButton = new ToggleButton (".c"));
    cTypeButton->addListener(this);
    cTypeButton->setToggleState(true, false);
    addAndMakeVisible (mTypeButton = new ToggleButton (".m"));
    mTypeButton->addListener(this);
    mTypeButton->setToggleState(true, false);
    addAndMakeVisible (mmTypeButton = new ToggleButton (".mm"));
    mmTypeButton->addListener(this);
    mmTypeButton->setToggleState(true, false);
    addAndMakeVisible (allFilesButton = new ToggleButton ("All Files"));
    allFilesButton->addListener(this);
    
    //search file controls
    fileToSearch = new FilenameComponent ("file to search",
                                          File::nonexistent,
                                          false, false, false,
                                          String::empty,
                                          String::empty,
                                          "Choose file to search");
    fileToSearch->addListener (this);					
	fileToSearch->setMaxNumberOfRecentFiles(10);
    addChildComponent (fileToSearch);
    
    
    //===========
    addChildComponent(disabledRegion = new Component());
    
    addAndMakeVisible(generateButton = new TextButton("Generate", "Generate"));
    generateButton->addListener(this);
    
    addAndMakeVisible(progressLabel = new Label("Progress Label"));
    progressLabel->setJustificationType(Justification::centred);
                      
}

AppComponent::~AppComponent()
{

}

//==============================================================================
void AppComponent::resized()
{
    //====translation file stuff=====
    newFileButton->setBounds((getWidth()/4), (getHeight()/15), getWidth()/4, 20);
    editFileButton->setBounds((getWidth()/4)*2, (getHeight()/15), getWidth()/4, 20);
    
    //new file stuff
    fileDirectory->setBounds((getWidth()/2)-100, (getHeight()/15)*2, 200, 20);
    fileNameEditor->setBounds((getWidth()/2)-100, (getHeight()/15)*3, 200, 20);
    languageEditor->setBounds((getWidth()/2)-100, (getHeight()/15)*4, 200, 20);
    countriesEditor->setBounds((getWidth()/2)-100, (getHeight()/15)*5, 200, 20);
    
    //existing file stuff
    fileLocation->setBounds((getWidth()/2)-100, (getHeight()/15)*2, 200, 20);
    
    //=== searching stuff=====
    searchDirectoryButton->setBounds((getWidth()/4), (getHeight()/15)*6, getWidth()/4, 20);
    searchFileButton->setBounds((getWidth()/4)*2, (getHeight()/15)*6, getWidth()/4, 20);
    
    //search directory
    directoryToSearch->setBounds((getWidth()/2)-100, (getHeight()/15)*7, 200, 20);
    fileTypeGroup->setBounds((getWidth()/2)-100, ((getHeight()/15)*8), 200, 100);
    cppTypeButton->setBounds((getWidth()/3), ((getHeight()/15)*9), 50, 20);
    hTypeButton->setBounds(((getWidth()/3)*2)-75, ((getHeight()/15)*9), 50, 20);
    mTypeButton->setBounds((getWidth()/3), ((getHeight()/15)*10), 50, 20);
    mmTypeButton->setBounds(((getWidth()/3)*2)-75, ((getHeight()/15)*10), 50, 20);
    cTypeButton->setBounds((getWidth()/3), ((getHeight()/15)*11), 50, 20);
    allFilesButton->setBounds(((getWidth()/3)*2)-75, ((getHeight()/15)*11), 75, 20);
    
    //search file
    fileToSearch->setBounds((getWidth()/2)-100, (getHeight()/15)*7, 200, 20);
    
    //====
    disabledRegion->setBounds(0, 0, getWidth(), getHeight());
    generateButton->setBounds((getWidth()/2)-50, (getHeight()/15)*13, 100, 20);
    progressLabel->setBounds((getWidth()/2)-200, (getHeight()/15)*14, 400, 20);
}

void AppComponent::buttonClicked (Button *button)
{
    if (button == generateButton)
    {
        if (isThreadRunning() == false) //When the button will display 'generate'
        {
            //=================================================================================
            //Do a bunch of checks to make sure all necessary data has been supplied by the user.
            //Alert the user of any missing data.
            //=================================================================================
            
            if ( ! (directoryToSearch->getCurrentFile() == File::nonexistent
                    && fileToSearch->getCurrentFile() == File::nonexistent))
            {
                bool shouldStartThread = true;
                
                if (newFileButton->getToggleState() == true) //create new file
                {
                    File translationFile(fileDirectory->getCurrentFile().getFullPathName() 
                                         + File::separatorString 
                                         + fileNameEditor->getText());
                    
                    if (fileNameEditor->getText() == String::empty)
                    {
                        AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, "No File Name Entered", "Please Choose a file name for the translation file.");
                        
                        shouldStartThread = false;
                    }
                    else if (translationFile.exists() == true)
                    {
                        bool shouldContinue = AlertWindow::showOkCancelBox(AlertWindow::WarningIcon, "File already exists", "The file you are trying to create already exists and will be overwritten. Do you want to continue?");
                        
                        if (shouldContinue == false)
                            shouldStartThread = false;
                        
                    }
                    
                }
                
                
                if (shouldStartThread == true)
                {
                    //==============================
                    //==============================
                    startThread();
                    //==============================
                    //==============================
                }
            }
            else
            {
                AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, "No search files selected", "Please choose a file or directory to search.");
            }
        }
        
        else //thread is running, so this button acts as a 'cancel' button
        {
            signalThreadShouldExit();
            
            button->setEnabled(false);
            button->setAlpha(0.5f);
        }
    }
    
    else if (button == newFileButton)
    {
        fileDirectory->setVisible(true);
        fileNameEditor->setVisible(true);
        languageEditor->setVisible(true);
        countriesEditor->setVisible(true);
        
        fileLocation->setVisible(false);
    }
    else if (button == editFileButton)
    {
        fileDirectory->setVisible(false);
        fileNameEditor->setVisible(false);
        languageEditor->setVisible(false);
        countriesEditor->setVisible(false);
        
        fileLocation->setVisible(true);
    }
    else if (button == searchDirectoryButton)
    {
        directoryToSearch->setVisible(true);
        fileTypeGroup->setVisible(true);
        cppTypeButton->setVisible(true);
        hTypeButton->setVisible(true);
        mTypeButton->setVisible(true);
        mmTypeButton->setVisible(true);
        cTypeButton->setVisible(true);
        allFilesButton->setVisible(true);
        
        fileToSearch->setVisible(false);    
    }
    else if (button == searchFileButton)
    {
        directoryToSearch->setVisible(false);
        fileTypeGroup->setVisible(false);
        cppTypeButton->setVisible(false);
        hTypeButton->setVisible(false);
        mTypeButton->setVisible(false);
        mmTypeButton->setVisible(false);
        cTypeButton->setVisible(false);
        allFilesButton->setVisible(false);
        
        fileToSearch->setVisible(true);    
    }
        
}


void AppComponent::filenameComponentChanged (FilenameComponent* filenameComponent)
{
    if (filenameComponent == fileLocation) //chosen an existing file to add to
    {
        String fileAsString = fileLocation->getCurrentFile().loadFileAsString();
        
        if (fileLocation->getCurrentFile().loadFileAsString().startsWith("language") == false)
        {
            AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, "Invalid File", "The selected file does not appear to be a Juce translation file.");
            
            filenameComponent->setCurrentFile(File::nonexistent, false, false);
        }
    }
}

void AppComponent::textEditorReturnKeyPressed (TextEditor &editor)
{
    
}

void AppComponent::run()
{
    bool cancelButtonPressed = true;
    
    while (! threadShouldExit())
    {
        {
            if (threadShouldExit() == true)
                break;
            
            const MessageManagerLock mmLock;
            generateButton->setButtonText("Cancel");
            progressLabel->setText("Searching... ", false);
            disabledRegion->setVisible(true);
        }
        
        File selectedFile;
        Array<File> filesToSearch;
        int noOfFiles = 0;
        
        //=================================================================================
        //=================================================================================
        
        
        if (searchDirectoryButton->getToggleState() == true) //if searching a directory
        {
            if (threadShouldExit() == true)
                break;
            
            selectedFile = directoryToSearch->getCurrentFile();
            
            //add all valid files in the directory to Array
            if (allFilesButton->getToggleState() == true)
            {
                noOfFiles += selectedFile.findChildFiles(filesToSearch, 6, true);
            }
            else
            {
                if (cppTypeButton->getToggleState() == true)
                    noOfFiles += selectedFile.findChildFiles(filesToSearch, 6, true, "*.cpp");
                if (hTypeButton->getToggleState() == true)
                    noOfFiles += selectedFile.findChildFiles(filesToSearch, 6, true, "*.h");
                if (mmTypeButton->getToggleState() == true)
                    noOfFiles += selectedFile.findChildFiles(filesToSearch, 6, true, "*.mm");
                if (cTypeButton->getToggleState() == true)
                    noOfFiles += selectedFile.findChildFiles(filesToSearch, 6, true, "*.c");
                if (mTypeButton->getToggleState() == true)
                    noOfFiles += selectedFile.findChildFiles(filesToSearch, 6, true, "*.m");
            }
            
            if (threadShouldExit() == true)
                break;
        }
        
        
        else if (searchFileButton->getToggleState() == true) //searching a single file
        {
            if (threadShouldExit() == true)
                break;
            
            //add single file to the array
            selectedFile = fileToSearch->getCurrentFile();
            filesToSearch.add(selectedFile);
            noOfFiles = 1;
        }
        
        std::cout << "Number of Files: " << noOfFiles << std::endl;
        
        
        
        //=================================================================================
        //=================================================================================
        
        
        
        //create an array to hold any matching string that need to be translated
        StringArray foundStrings;
        
        
        //search through each file in the array looking for the matching strings
        //and add the relevent strings to the StringArray
        for (int x = 0; x < noOfFiles; x++)
        {
            if (threadShouldExit() == true)
                break;
            
            //get file as string
            String fileAsString = filesToSearch[x].loadFileAsString();
            
            {
                const MessageManagerLock mmLock;
                progressLabel->setText("Searching... " + filesToSearch[x].getFileName(), false);
            }
            
            String stringToFind("translate(\"");
            int currentIndex = 0;
            bool finishedSearch = false;
            
            while (finishedSearch == false)
            {
                if (threadShouldExit() == true)
                    break;
                
                int startIndex = fileAsString.indexOf(currentIndex, stringToFind) + 10;
                
                //if an/another instance of the string appears in the file...
                if (startIndex != 9) //-1 which means not found stringToFind, + 10)
                {
                    int endIndex = fileAsString.indexOf(startIndex, "\")") + 1;
                    String subString = fileAsString.substring(startIndex, endIndex);
                    foundStrings.add(subString);
                    
                    currentIndex = endIndex;
                }
                //if no/no more instances are in the file, stop searching
                else
                {
                    finishedSearch = true;
                }
            }
            
            
            stringToFind = "TRANS(\"";
            currentIndex = 0;
            finishedSearch = false;
            
            while (finishedSearch == false)
            {
                if (threadShouldExit() == true)
                    break;
                
                int startIndex = fileAsString.indexOf(currentIndex, stringToFind) + 6;
                
                //if an/another instance of the string appears in the file...
                if (startIndex != 5) //-1 which means not found stringToFind, + 6)
                {
                    int endIndex = fileAsString.indexOf(startIndex, "\")") + 1;
                    String subString = fileAsString.substring(startIndex, endIndex);
                    foundStrings.add(subString);
                    
                    currentIndex = endIndex;
                }
                //if no/no more instances are in the file, stop searching
                else
                {
                    finishedSearch = true;
                }
                
            }
            
            
            if (threadShouldExit() == true)
                break;
            
        }
        
        
        
        //=================================================================================
        //=================================================================================
        
        
        
        
        if (foundStrings.size() > 0)
        {
            if (threadShouldExit() == true)
                break;
            
            //remove any duplicates
            foundStrings.removeDuplicates(false);
            
            
            if (newFileButton->getToggleState() == true) //create new file
            {
                if (threadShouldExit() == true)
                    break;
                
                File translationFile(fileDirectory->getCurrentFile().getFullPathName() 
                                     + File::separatorString
                                     + fileNameEditor->getText());
                translationFile.create();
                
                translationFile.replaceWithText("language: " + languageEditor->getText() + "\n");
                translationFile.appendText("countries: " + countriesEditor->getText() + "\n\n");
                
                for (int i = 0; i < foundStrings.size(); i++)
                {
                    translationFile.appendText(foundStrings[i] + " = \"\"\n");
                    std::cout << foundStrings[i] << std::endl;
                }
                
                
                {
                    const MessageManagerLock mmLock;
                    progressLabel->setText("File successfully created! ", false);
                }
                
                if (threadShouldExit() == true)
                    break;
            }
            
            else if (editFileButton->getToggleState() == true) //add to existing file
            {
                if (threadShouldExit() == true)
                    break;
                
                File translationFile(fileLocation->getCurrentFile());
                String transFileAsString = translationFile.loadFileAsString();
                
                for (int i = 0; i < foundStrings.size(); i++)
                {
                    //first compare strings in array with ones already in file, and don't add any duplicates to file
                    int shouldAdd = transFileAsString.indexOf(foundStrings[i]);
                    if (shouldAdd == -1) //if foundString[i] has not been found in the trans file
                    {
                        translationFile.appendText(foundStrings[i] + " = \"\"\n");
                        std::cout << foundStrings[i] << std::endl;
                    }
                }
                
                
                {
                    const MessageManagerLock mmLock;
                    progressLabel->setText("Data added to file successfully! ", false);
                }
                
                
                if (threadShouldExit() == true)
                    break;
            }
            
            
        }
        
        
        else
        {
            if (threadShouldExit() == true)
                break;
            
            const MessageManagerLock mmLock;
            progressLabel->setText("No strings found!", false);
        }
        
        
        signalThreadShouldExit();
        cancelButtonPressed = false;
        
    } //end of while loop
    
    //=================================================================================
    //=================================================================================
    
    if (cancelButtonPressed == true)
    {
        {
            const MessageManagerLock mmLock;
            progressLabel->setText("Process cancelled!", false);
        }
    }

    
    //reset GUI attributes
    {
        const MessageManagerLock mmLock;
        generateButton->setButtonText("Generate");
        generateButton->setEnabled(true);
        generateButton->setAlpha(1.0f);
        disabledRegion->setVisible(false);
    }
}
