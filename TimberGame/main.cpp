#include <SFML/Graphics.hpp>
#include <iostream>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

//Declaring the use of sf namespace (no need for sf::Texture, for example).
using namespace sf;
using namespace std;

int main(){
    //Creating instances of texture and sprite objects.
    Texture textureBackground;
    Sprite spriteBackground;
    
    Texture textureTree;
    Sprite spriteTree;
    
    Texture textureBee;
    Sprite spriteBee;
    
    Texture textureCloud;
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    
    //Declaring the file which will be the texture.
    textureBackground.loadFromFile("/Users/renan/Documents/C++/SFML_Project/TimberGame/TimberGame/graphics/background.png");
    textureTree.loadFromFile("/Users/renan/Documents/C++/SFML_Project/Timber/Timber/graphics/tree.png");
    textureBee.loadFromFile("/Users/renan/Documents/C++/SFML_Project/Timber/Timber/graphics/insect.png");
    textureCloud.loadFromFile("/Users/renan/Documents/C++/SFML_Project/Timber/Timber/graphics/cloud.png");
    
    //Setting the created texture to be the sprite.
    spriteBackground.setTexture(textureBackground);
    spriteTree.setTexture(textureTree);
    spriteBee.setTexture(textureBee);
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    
    //Setting position of the sprite on the screen.
    spriteBackground.setPosition(0,0);
    spriteTree.setPosition(600,0);
    spriteBee.setPosition(-100,800);
    spriteCloud1.setPosition(-320,0);
    spriteCloud2.setPosition(-320,15);
    spriteCloud3.setPosition(-320,10);
    
    //Cloud related variables.
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;
    
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;
    
    //Bee related variables.
    bool beeActive = false;
    float beeSpeed = 0.0f;
    
    //Text variables.
    int scorePoints = 0;
    
    //Creating window based on VideoMode.
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Timber", Style::Fullscreen);
    
    //Declaring clock object
    Clock clock;
    
    RectangleShape timeBar;
     
    float timeBarWidth = 600;
    float timeBarHeight = 50;
    
    timeBar.setSize(Vector2f(timeBarWidth,timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(1920/2 - 500, 830);
    
    Time gameTotalTime;
    float timeRemaining = 30;
    float timeBarWidthPerSecond = timeBarWidth / timeRemaining;
    
    //Declaring boolean that defines if the game is running.
    bool paused = true;
    
    //Mainloop of the game.
    while(window.isOpen()){
        
        Event event;
        
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
            }
        }
        
        //Closes the tab in case that ESC is pressed on the keyboard.
        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            window.close();
        }
        
        //Starts the game.
        if(Keyboard::isKeyPressed(Keyboard::Return)){
            paused = false;
            
            scorePoints = 0;
            timeRemaining = 30;
        }
        
        //If time remaining gets to zero game restarts.
        if(timeRemaining <= 0.0){
            paused = true;
            spriteBee.setPosition(-100,800);
            spriteCloud1.setPosition(-320,0);
            spriteCloud2.setPosition(-320,15);
            spriteCloud3.setPosition(-320,10);
            
            scorePoints = 0;
            timeRemaining = 30;
        }
        
        //Reseting the clock with time.
        Time dt = clock.restart();
        
        Font font;
        
        if(!font.loadFromFile("/Users/renan/Documents/C++/SFML_Project/External_Libraries/Fonts/arial-black.ttf")){
            cout << "Cannot find the specified font" << endl;
            
            system("pause");
        }
        
        String sentence;
        String myScore;
        String counter;
        
        Text beePosition(sentence, font, 40);
        Text score(myScore , font, 40);
        Text countdown(counter, font, 40);
        
        score.setPosition(0, 60);
        countdown.setPosition(0, 120);
        
        beePosition.setString("Bee Position: " + to_string(beeSpeed));
        score.setString("Score: " + to_string(scorePoints));
        countdown.setString("Time Remaining: " + to_string(timeRemaining));
        
        
        //Checking if the game is paused.
        if(!paused){
                        
            //Run timer and bar.
            timeRemaining -= dt.asSeconds();
            
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining , timeBarHeight));
            /**
             Bee animation control.
             */
            if(!beeActive){
                //How fast the bee is.
                //Generating a random number based on time.
                srand((int)time(0) * 10);
                //Getting random number between 199-399.
                beeSpeed = (rand() % 200) + 200;
                
                //How high the bee is.
                //Generating a random number based on time.
                srand((int)time(0) * 10);
                //Getting random number between 499-999.
                float height = (rand() % 200) + 200;
                spriteBee.setPosition(-100, height);
                beeActive = true;
            }else{
                //Move the bee.
                
                spriteBee.setPosition(spriteBee.getPosition().x + (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
                
                beePosition.setString(to_string(spriteBee.getPosition().x));
                
                //Checking if the bee has got onto the left hand of the screen.
                if(spriteBee.getPosition().x > 1600){
                    scorePoints++;
                    beeActive = false;
                }
                
            }
            
            /**
             Cloud 1 animation control.
             */
            if(!cloud1Active){
                //How fast the bee is.
                //Generating a random number based on time.
                srand((int)time(0) * 10);
                //Getting random number between 199-399.
                cloud1Speed = (rand() % 100) + 115;
                spriteCloud1.setPosition(-450, 10);
                cloud1Active = true;
            }else{
                //Move the bee.
                
                spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);
                
                //Checking if the bee has got onto the left hand of the screen.
                if(spriteCloud1.getPosition().x > 1600){
                    cloud1Active = false;
                }
                
            }
            /**
             Cloud 2 animation control.
             */
            if(!cloud2Active){
                //How fast the bee is.
                //Generating a random number based on time.
                srand((int)time(0) * 20);
                //Getting random number between 199-399.
                cloud2Speed = (rand() % 135) + 130;
                spriteCloud2.setPosition(-800, 45);
                cloud2Active = true;
            }else{
                //Move the bee.
                
                spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);
                
                //Checking if the bee has got onto the left hand of the screen.
                if(spriteCloud2.getPosition().x > 1600){
                    cloud2Active = false;
                }
                
            }
            
            /**
             Cloud 3 animation control.
             */
            if(!cloud3Active){
                //How fast the bee is.
                //Generating a random number based on time.
                srand((int)time(0) * 20);
                //Getting random number between 199-399.
                cloud3Speed = (rand() % 200) + 190;
                spriteCloud3.setPosition(-300, 25);
                cloud3Active = true;
            }else{
                //Move the bee.
                
                spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);
                
                //Checking if the bee has got onto the left hand of the screen.
                if(spriteCloud3.getPosition().x > 1600){
                    cloud3Active = false;
                }
                
            }
        }
        
        //Clearing from last frame.
        window.clear();
        
        //Drawing the sprite on the screen.
        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.draw(beePosition);
        window.draw(score);
        window.draw(countdown);
        window.draw(timeBar);
        
        //Displaying what was draw on the screen.
        window.display();
    }
}
