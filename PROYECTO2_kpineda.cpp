#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class ImageEditor {
private:
    Image firstImage;    
    Image secondImage;   
    Texture texture1;    
    Texture texture2;    
    Sprite sprite1;      
    Sprite sprite2;      
    bool changeColorOfPicture; 
public:
    ImageEditor(Image first, Image second) {
        firstImage = first;
        secondImage = second;
        changeColorOfPicture = false;  
    }
    void keyboardEvents(RenderWindow& originalWindow, RenderWindow& processedWindow) {
        Event event;
        while (originalWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                originalWindow.close();
            }
        }
        while (processedWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                processedWindow.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::A) {  
                    changeBlackAndWhite();       
                    texture2.loadFromImage(secondImage);  
                    sprite2.setTexture(texture2);         
                }
            }
        }
    }
    void showImages() {   
        RenderWindow originalWindow(VideoMode(firstImage.getSize().x, firstImage.getSize().y), "Original Image");
        RenderWindow processedWindow(VideoMode(secondImage.getSize().x, secondImage.getSize().y), "Processed Image");
        texture1.loadFromImage(firstImage);
        texture2.loadFromImage(secondImage);   
        sprite1.setTexture(texture1);
        sprite2.setTexture(texture2); 
        while (originalWindow.isOpen() && processedWindow.isOpen()) {
            keyboardEvents(originalWindow, processedWindow);
            originalWindow.clear(Color::White);
            originalWindow.draw(sprite1);
            originalWindow.display();
            processedWindow.clear(Color::White);
            processedWindow.draw(sprite2);
            processedWindow.display();
        }
    }
    void applyBlackAndWhiteFilter() {
        int width = secondImage.getSize().x;
        int height = secondImage.getSize().y;     
        for (int x = 0; x < width; x++) { 
            for (int y = 0; y < height; y++) {  
                Color color = firstImage.getPixel(x, y);          
                int filterBW = (color.r * 0.299) + (color.g * 0.587) + (color.b * 0.114); 
                Color greyPixel(filterBW, filterBW, filterBW);  
                secondImage.setPixel(x, y, greyPixel);  
            } 
        } 
    }
    void changeBlackAndWhite() {
        if (changeColorOfPicture) {
            secondImage = firstImage;
        }
        else {
            applyBlackAndWhiteFilter();
        }
        changeColorOfPicture = !changeColorOfPicture;
    }
};
int main() {
    Image image;
    if (!image.loadFromFile("C:/Users/Keylo/Downloads/la-noche-estrellada.png")) {
        cout << "Error!" << endl;
        return -1;
    }
    Image secondImage = image;
    ImageEditor editor(image, secondImage);
    editor.showImages();  
    return 0;
}