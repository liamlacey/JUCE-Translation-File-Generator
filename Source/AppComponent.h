/*
 *  AppComponent.h
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

#ifndef H_APPCOMPONENT
#define H_APPCOMPONENT

#include "../JuceLibraryCode/JuceHeader.h"

class AppComponent  :   public Component,
                        public Button::Listener,
                        public FilenameComponentListener,
                        public TextEditor::Listener,
                        public Thread
                        
{	
public:
	//==============================================================================
	AppComponent();
	~AppComponent();
	//==============================================================================
	void resized();
    void buttonClicked (Button *button);
    void filenameComponentChanged (FilenameComponent* filenameComponent);
    void textEditorReturnKeyPressed (TextEditor &editor);
    
    void run(); //used to search files and create the translation file
    
	//==============================================================================
private:
	//==============================================================================
    
    //======translation file controls=========
    ScopedPointer <TextButton> newFileButton, editFileButton;
    
    //new file stuff
    ScopedPointer <FilenameComponent> fileDirectory;
    ScopedPointer <TextEditor> fileNameEditor, languageEditor, countriesEditor;
    
    //edit file stuff
    ScopedPointer <FilenameComponent> fileLocation;
    
    //======Search controls=========
    ScopedPointer <TextButton> searchFileButton, searchDirectoryButton;
    
    //search file stuff
    ScopedPointer <FilenameComponent> fileToSearch;
    
    //search directory stuff
    ScopedPointer <FilenameComponent> directoryToSearch;
    ScopedPointer <GroupComponent> fileTypeGroup;
    ScopedPointer <ToggleButton> cppTypeButton, cTypeButton, hTypeButton, mmTypeButton, mTypeButton, allFilesButton;
    
    //========
    ScopedPointer <TextButton> generateButton;
    ScopedPointer <Label> progressLabel;
    
    ScopedPointer <Component> disabledRegion;   //this is used as a hacky way of 'disabling' the majority of
                                                //the components when the thread is running, by adding an invisible
                                                //component on top. 
	
};



#endif // H_APPCOMPONENT