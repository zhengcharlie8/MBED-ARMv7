#include "mbed.h"
#include "ILI9340_Driver.h"
#include "stdlib.h"
#include <vector>
#include <string>
using namespace std;

DigitalIn pb1(p15);
DigitalIn pb2(p16);
DigitalIn pb3(p17);
DigitalIn pb4(p18);
DigitalIn pb5(p19);
//PwmOut speaker(p21);

//Play notes
class Speaker
{
public:
    Speaker(PinName pin) : _pin(pin) {
// _pin(pin) means pass pin to the Speaker Constructor
    }
// class method to play a note based on PwmOut class
    void PlayNote(float frequency, float duration, float volume) {
        _pin.period(1.0/frequency);
        _pin = volume/2.0;
        wait(duration);
        _pin = 0.0;
    }
 
private:
// sets up specified pin for PWM using PwmOut class 
    PwmOut _pin;
};


int main() {
    float cNote=261.6;
    float cSharp=277.2;
    float dNote=293.7;
    float dSharp=311.1;
    float eNote=329.6;
    float fNote=349.2;
    float fSharp=370.0;
    float gNote=392.0;
    float gSharp=415.3;
    float aNote=440.0;
    float aSharp=466.2;
    float bNote=493.9;

    int notes[12]={cNote, cSharp, dNote, dSharp, eNote, fNote, fSharp, gNote, gSharp, aNote, aSharp, bNote};
    char* noteNames[12]={"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};


    Speaker mySpeaker(p21);
    vector<int> startSong;
    startSong.push_back(cNote);
    startSong.push_back(dNote);
    startSong.push_back(eNote);
//    startSong.push_back(fNote);
//    startSong.push_back(eNote);
//    startSong.push_back(dNote);
//    startSong.push_back(cNote);
    
    bool play=true;    
    // create the display object
    ILI9340_Display tft = ILI9340_Display(p5, p6, p7, p8, p9, p10);

    // initialise the display
    tft.DispInit();
    
    // clears the screen to remove all noise data
    tft.FillScreen(ILI9340_BLACK); 
        
    //speaker.period(1.0/500.0);
    vector<char> vec;
    vector<char> key(5,'a');
    while(true) {
        if(play){
        for(int i=0; i<startSong.size();i++){
        mySpeaker.PlayNote(startSong[i],0.5,0.5);
        }
        play=false;
        }   
        //(String, position x, position y, size, colour)
        tft.DrawString("Enter Password", 10, 100, 2, ILI9340_WHITE); 
//        tft.DrawString("Timer Countdown:", 70, 135, 1, ILI9340_BLACK);
        //tft.DrawString("Go Create!", 45, 210, 2, ILI9340_BLUE);
    
        // convert the RGB values into values that can be writen to the screen
        if(pb1){
        vec.push_back('a');
        mySpeaker.PlayNote(fNote,0.5,0.5);
        while(pb1){}   
        }
        else if(pb2){
        vec.push_back('b');
        mySpeaker.PlayNote(gNote,0.5,0.5);
        while(pb2){}    
        }
        if(pb3){
        vec.push_back('c');
        mySpeaker.PlayNote(aNote,0.5,0.5);
        while(pb3){}     
        }
        if(pb4){
        vec.push_back('d');
        mySpeaker.PlayNote(bNote,0.5,0.5);
        while(pb4){}   
        }
        // Print a 'waiting..' animation to the screen.
        if(vec.size() == 1)
        tft.FillRect(30, 150, 20, 20, ILI9340_WHITE);
        else if (vec.size()==2)
        tft.FillRect(70, 150, 20, 20, ILI9340_WHITE);
        else if (vec.size()==3)
        tft.FillRect(110, 150, 20, 20, ILI9340_WHITE);
        else if (vec.size()==4)
        tft.FillRect(150, 150, 20, 20, ILI9340_WHITE);
        else if (vec.size()==5){
        tft.FillRect(190, 150, 20, 20, ILI9340_WHITE);
        wait(1);
        bool wrong = 0;
        for(int i = 0; i<5; i++){
            if(vec[i] != key[i])
                {
                    tft.FillScreen(ILI9340_BLACK); 
                    tft.DrawString("Wrong Password", 10, 100, 2, ILI9340_RED); 
                    mySpeaker.PlayNote(1661.2 , 3.0,0.5);
                    tft.FillScreen(ILI9340_BLACK); 
                    vec.clear();
                    wrong = 1;
                    break;
                        }
        }
        if(!wrong){
        mySpeaker.PlayNote(293.6, 0.125, 0.5); //D
        mySpeaker.PlayNote(293.6, 0.125, 0.5); //D
        mySpeaker.PlayNote(587.3, 0.25, 0.5); //d
        mySpeaker.PlayNote(440.0, 0.25, 0.5); //a
        wait(0.125);
        mySpeaker.PlayNote(415.3, 0.25, 0.5); //G# 
        mySpeaker.PlayNote(391.9, 0.25, 0.5); //G
        mySpeaker.PlayNote(349.2, 0.25, 0.5); //F
        mySpeaker.PlayNote(293.6, 0.125, 0.5); //D
        mySpeaker.PlayNote(349.2, 0.125, 0.5); //F
        mySpeaker.PlayNote(391.9, 0.125, 0.5); //G
        vec.clear();
        tft.FillScreen(ILI9340_BLACK); 
        tft.DrawString("Access Granted", 10, 100, 2, ILI9340_GREEN);
        tft.DrawString("A to return", 10, 125, 1, ILI9340_WHITE);
        tft.DrawString("B to change Password", 10, 150, 1, ILI9340_WHITE);
        tft.DrawString("C to change start music",10, 175, 1, ILI9340_WHITE);
        bool done = 0;
        while(!pb1 || !pb2 || !pb3)
        {
        if(pb1){
            tft.FillScreen(ILI9340_BLACK);
            break;
            } 
        else if(pb2){
        tft.FillScreen(ILI9340_BLACK);
        tft.DrawString("New Password", 25, 100, 2, ILI9340_WHITE);
        key.clear();
        while(key.size() <= 5){
        if(pb1){
        key.push_back('a');
        mySpeaker.PlayNote(fNote,0.5,0.5);
        while(pb1){}   
        }
        else if(pb2){
        key.push_back('b');
        mySpeaker.PlayNote(gNote,0.5,0.5);
        while(pb2){}    
        }
        if(pb3){
        key.push_back('c');
        mySpeaker.PlayNote(aNote,0.5,0.5);
        while(pb3){}     
        }
        if(pb4){
        key.push_back('d');
        mySpeaker.PlayNote(bNote,0.5,0.5);
        while(pb4){}   
        } 
        if(key.size() == 1)
        tft.FillRect(30, 150, 20, 20, ILI9340_WHITE);
        else if (key.size()==2)
        tft.FillRect(70, 150, 20, 20, ILI9340_WHITE);
        else if (key.size()==3)
        tft.FillRect(110, 150, 20, 20, ILI9340_WHITE);
        else if (key.size()==4)
        tft.FillRect(150, 150, 20, 20, ILI9340_WHITE);
        else if (key.size()==5){
        tft.FillRect(190, 150, 20, 20, ILI9340_WHITE);
        wait(1);
        tft.FillScreen(ILI9340_BLACK);
        tft.DrawString("Password Set", 25, 100, 2, ILI9340_WHITE);
        wait(3);
        tft.FillScreen(ILI9340_BLACK);
        done = 1;
        play=1;
        break;
        }
        }
        }
        else if(pb3){
            int index=0;
            startSong.clear();
            int count=10;
            while(count!=0){
                tft.FillScreen(ILI9340_BLACK);
                tft.DrawString("Choose up to", 10, 100, 2, ILI9340_WHITE);
                tft.DrawString("10 Notes", 10, 125, 2, ILI9340_WHITE);
                tft.DrawString(noteNames[index], 75, 175, 2, ILI9340_WHITE);
                mySpeaker.PlayNote(notes[index],0.5,0.5);
                while(!pb1 || !pb2 ||!pb3 || !pb4){
                if(pb2){
                    if((index+1)<12)
                        index++;
                    while(pb2){}
                    break;
                }
                else if(pb1){
                    if(index-1>=0)
                        index--;
                    while(pb1){}   
                    break; 
                }

                else if(pb3){
                    startSong.push_back(notes[index]);
                    mySpeaker.PlayNote(notes[index],0.5,0.5);
                    count--;
                    while(pb3){}
                    wait(1.0);
                    break;
                }
                
                else if(pb4){
                 while(pb4){}
                 count=0;
                 break;
                 }
                 }
            }
            tft.FillScreen(ILI9340_BLACK);
            tft.DrawString("New Song Set", 25, 100, 2, ILI9340_WHITE);
            wait(2.0);
            tft.FillScreen(ILI9340_BLACK);            
            done=1;
            play=1;
            
        }
        if(done)
        break;
        }
           
        wait(.025);

    }
        }

}
}