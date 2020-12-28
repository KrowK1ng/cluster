#include<iostream>
#include<cmath>
#include<thread>
#include<vector>
#include<string>

#include"ftxui/component/input.hpp"
#include"ftxui/component/screen_interactive.hpp"
#include"ftxui/component/container.hpp"
#include"ftxui/component/menu.hpp"
#include"ftxui/screen/string.hpp"
#include"ftxui/dom/elements.hpp"

using namespace ftxui;
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
            temp.message = "I am your father aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa ";
            messages.push_back(temp);
            for(int i = 0; i < messages.size(); i++){
                //temp_message = hflow(paragraph(to_wstring(messages[i].Output())));
                temp_message = text(to_wstring(messages[i].Output()));
                emessages.push_back(temp_message);
            }
            emessages.push_back(filler());
        }
        
        Element Render() override{
            return window(text(L"Nerd Club") ,vbox(emessages));
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
                type_field.Render() | border,
            });
        }
};

int main(int argc, const char* argv[]){
    auto screen = ScreenInteractive::Fullscreen();

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
