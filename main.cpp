#include<iostream>
#include<cmath>
#include<thread>
#include<vector>
#include<string>
#include <algorithm>

#include"ftxui/component/input.hpp"
#include"ftxui/component/screen_interactive.hpp"
#include"ftxui/component/container.hpp"
#include"ftxui/component/menu.hpp"
#include"ftxui/component/button.hpp"
#include"ftxui/screen/string.hpp"
#include"ftxui/screen/terminal.hpp"
#include"ftxui/dom/elements.hpp"

using namespace ftxui;

int screenw, screenh;

Element string_parser(std::string message, int limitsize){
    std::vector<std::string>line;                   //vector of lines
    std::vector<Element>lines;
    std::string temp_string;
    
    int i;                                          //faster for "for" loop
    int clines = 1;                                 //number of lines
    /*for(char c : message){
        if(c == ' '){    //checks if space
            if(findword){
                temp_string = message.substr(lastpos,position - lastpos)
            }
        }
    }*/

    while(message.length() > limitsize){
        if(message[limitsize] == ' '){      //if line ends with space
            temp_string = message.substr(0,limitsize);
            message = message.substr(limitsize);
        }else{
            for(i = limitsize - 1; i >= 0; i--){
                if(message[i] == ' '){
                    temp_string = message.substr(0,i);
                    message = message.substr(i + 1);
                    i = -2;
                }
            }
            if(i == -1){
                temp_string = message.substr(0,limitsize);
                message = message.substr(limitsize);
            }
        }
        
        line.push_back(temp_string);
        clines++;
    }
    line.push_back(message);

    for(i = 0; i < clines; i++){
        lines.push_back(text(to_wstring(line[i])));
    }

    return vbox(lines);
}

class Message {
    public:
        std::string sender;
        std::string message;

        std::string Output(){
            //return std::strcat(std::strcat(std::strcat(sender , " : "), message ), "\n");
            return sender + " : " + message;
        }
};

class Messages : public Component {
    public:
        std::vector<Message> messages;
        std::vector<Element> emessages;
        Element temp_message;
        std::string total = "";
        Message temp;

        Messages(){
            temp.sender = "Jora";
            temp.message = "Hello";
            messages.push_back(temp);
            temp.sender = "Lcuk";
            temp.message = "Hello indeed";
            messages.push_back(temp);
            temp.sender = "Jora";
            //temp.message = "I am your father";
            temp.message = "I am your father aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa ";
            messages.push_back(temp);
            temp.sender = "Lcuk";
            temp.message = "Here is the alphabet abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
            messages.push_back(temp);
            for(int i = 0; i < messages.size(); i++){
                emessages.push_back(string_parser(messages[i].Output(), screenw - 2));
            }
        }
        
        Element Render() override{
            /*for(int i = 0; i < messages.size(); i++){
                Requirement require = hflow(paragraph(to_wstring(messages[i].Output())))->requirement() ;
                temp_message = text(to_wstring(std::to_string(require.min_x) + std::to_string(require.min_y)));
                emessages.push_back(temp_message);
            }*/
            //return window(text(L"Nerd Club") ,(vbox(emessages)));
            return window(text(L"Nerd Club") ,(vbox(emessages)));
        }
};

class TypeField : public Component {
    public:
        Container type_field = Container::Horizontal();
        Input input;
    
        TypeField(){
        
            Add(&type_field);

            //Input field
            input.placeholder = L"Type message...";
            type_field.Add(&input);
        }

        Element Render() override {
            return hbox({
                input.Render() | flex,
            });
        }
};

class Header : public Component{
    public:
        Container main_container = Container::Vertical();
        TypeField type_field;
        Messages message_field;

        Header(){
            Add(&main_container);

            main_container.Add(&type_field);
            main_container.Add(&message_field);
        }

        Element Render() override{
            return vbox({
                text(L"Textinger") | bold | hcenter,
                //window(text(L"InfoClub") , text(L"Hello, It's me")) | flex,
                message_field.Render() | flex,
                //message_field.Render() ,
                type_field.Render() | border,
            });
        }
};

int main(int argc, const char* argv[]){
    auto screen = ScreenInteractive::Fullscreen();

    screenw = Terminal::Size().dimx;
    screenh = Terminal::Size().dimy;

    std::thread update([&screen]() {
        for(;;){
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(0.05s);
            screen.PostEvent(Event::Custom);
        }
    });
    Header tab;
    screen.Loop(&tab);

    return 0;
}
