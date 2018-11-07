# Introduction
Before we start coding and building this prototype, I will first explain what this prototype does and how it works. 

First of all, this prototype is builded in `Arduino` and a LEDstrip. Other programs that also have been used for this are:`Adafruit`, `Zapier` and `Slack` (later this will be further explained). 

### "BUT WHAT DOES THIS PIECE OF CODE DO?!"

Well, what this code exactly does is when you recieve a message on Slack in the chatroom `general`, you will recieve a notification. The notification is displayed in the LED strip that is connected to your arduino.

# Alright, so how do I start?
First of all you need to create an account on Zapier (https://zapier.com/) and Adafruit (https://io.adafruit.com/). After you made an account we can start with building.

## Adafruit
When your account is created, are there a few steps to do:
  1. Click on `View AIO Key` and copy the Username and Active Key on a place where you can easily find it (you will need it for later).
  2. Go to `Feeds`and create a new feed. 
  3. Give it a name how you want it.
  4. When these steps are done, we can move on to `zapier`.
  
<img width="1280" alt="screenshot 2018-11-07 22 40 01" src="https://user-images.githubusercontent.com/32538678/48162738-2d929b80-e2de-11e8-8580-fbf41ed0b5d2.png">


## Zapier
Everything is filled in on Adafruit, so we can start with Zapier. After your Zapier account is created, we can start by clicking on `Make a Zap`

![screenshot 2018-11-07 21 10 11-01](https://user-images.githubusercontent.com/32538678/48161418-cc1cfd80-e2da-11e8-9a9c-a9c4cebce6df.png)

When you created a Zap we need to do a few steps:
1. In the trigger block, we should first start looking for `Slack`.
2. Choose `New Message Posted to Channel`.
3. Choose your Slack account where you want to connect the LED with it.
4. Save and continue.
5. Choose the channel that you want to connect the led with (I have chosen for #general).
6. `Trigger for Bot Messages?`I have kept it the same way.
7. Click on `Pull in samples` and continue.

Almost done! Now we need to connect Zapier with Adafruit.

8. Add a step and click on `Action/Search`.
9. Search for `Adafruit`.
10. Save and continue.
11. Connect it with your Adafruit account where your feed was created. 
12. Save and continue.
13. Fill in the value you want to give when a message is sended in Slack (I filled in 1).
14. In `feed` you need to fill in the feedname we just created in Adafruit. 
15. Test this step.

If you go to Adafruit and you click on your created feed, you can see that your Zapier just sended the value 1.

## Yes it works! Oh wait, what about my LED?!
Okay, now it works with Zapier and Adafruit! The next step is to download the `example_slacktest` file from github. When you downloaded the document, we need to do the following steps:

1. Open the document.
2. Connect your LED strip in your NODE (I have used `pinmode D5`).
3. Go to the next tab `config.h`.
4. Fill in  `WIFI_SSID` with your own `Wifi SSID`.
5. Fill in  `WIFI_PASS` with your own `Wifi Password`.
6. Fill in  `WIO_USERNAME` with your Adafruit `Username`.
7. Fill in  `IO_KEY` with your Adafruit `Active Key`.
8. Upload your code and open your `serial monitor`. 
9. Set your serial on `115200 baud`.

Is your Arduino connected? Great! Go to Slack and open the channel where your Arduino is connected with. Type something in the chat.

And? Did it turn on the leds blue?

# Yes it works!
Nice!

## Can I change it into an another color?
To change the color you can edit the code in the `void handleNumber(AdafruitIO_Data *data)`.

If you can see in the code, I have used an `if/else` statement. 

```  
void handleNumber(AdafruitIO_Data *data) {
    
    Serial.println("Received Number: ");
    Serial.println(data->value());

    int slacktest = data->toInt();

    if(slacktest == 1){
        for(int i=0; i<18; ++i) {
        strip.setPixelColor(i, 0, 0, 255);
        }
      
      strip.show();
    } else if (slacktest  == 2) {
      
        strip.setBrightness(0);
        strip.show();
    }else {
      strip.setBrightness(30);
       strip.show();
    }
    
}

```

In the `if statement` you can see that if the `value is 1`, the strip have to set the color `Blue`. If you want to change it to an another color, you can change the RGB-color.
