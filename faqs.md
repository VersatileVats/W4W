### Question 1: Why did I make this project?

The utmost and essential thing for human survival is undoubtedly **water**. It is rightly said the _“Elixir of Life”_. When science blossomed, mankind witnessed many revolutionary inventions which includes **electricity, locomotives, automobiles, modes of communication, astronomical observations**, and many more which paved the way for what we are at this point.

<p align="center">
Tough times create strong men, <br>
strong men create easy times, <br>
easy times create weak men, <br>
weak men create tough times 
</p>

Our ancestors went through the tough phase and discovered how important is water for survival but we are now not looking for conservation of this precious resource. We are depleting this non-renewable resource at such a fast pace that future generations will be again doing the hard work to conserve water. So, through this project, we tried to do our best to conserve 2,000,000,000 liters of water annually which was wasted by the **overflowing water tanks**, so that mankind can cherish this beautiful resource for eternity.

### Question 2: Why do we I robotics in this project?

I used robotics in the project because humans are more fascinated by the fact that a robot can do normal chores in real life. **Amazon prime air** is a drone-based delivery method adopted in many nations. Many companies like **Uber, Ola** are doing successful trials of aerial transportation. So, I thought it would be great if I can somehow incorporate a robot in the project which will add a new dimension to it. Hold on, this robot is not like the others which are being controlled by an **Arduino**, it is being controlled by NodeMCU microcontroller which sets it apart from the crowd.

### Question 3: What are the unique points of the robot?

The robot is being controlled by **NodeMCU** – an Internet-equipped chip. I used NodeMCU in order to make the robot communicate with the Arduino setup so that the robot can work accordingly. The uniqueness’s of the robot are:

1. NodeMCU has only 1 analog pin, but in case to control the 2 motors of the robot we needed at least 2 analog ports to send the signals of 2 IR sensors. In Arduino, there are 5 analog ports, but I have to send 2 analog signals concurrently to a single port of NodeMCU. I did this by incorporating **CD4051 multiplexer IC**. Not only that, I have to synchronize it with the **L293D motor driver shield** so that the whole execution at the robot end is good to go. Using the multiplexer IC with the motor driver shield was also quite a bit of a challenge as the CD4051 multiplexer IC is a 03 select line-based (S0, S1, and S2) multiplexer. This means that I can insert **2^3 = 8 analog sensors** with this IC and use the single port i.e. A0 of the NodeMCU to read all 8 values. But in my case, I used only 2 IR sensors which means I don’t know what I have to do with the third select pins? In many attempts, the third select line was giving random values which we did not even need. After some trials, I got to know that the third select line must be provided a voltage of 0 so that the pin should not float.

2. While using the Integromat scenarios, I was not sure how to create a scenario and how to integrate it into our programming? I have used 6 scenarios for the project which includes various CRUD operations. It was challenging to get the response in the Nodemcu because the response there comes in a format that needs to be separated as per our needs. So, it was good to deliver the working scenarios.

### Question 3: What are the accomplishments of this project that we are proud of?

1. As already mentioned in the starting that I will be creating 4 custom options for the project and I did that. I have created the website, incorporated the capacitive touch sensor, automated the voice control thing, and created the cloud dashboard.

2. This is a project which can be deployed in the market as it is almost optimized. It is also cost-efficient as the whole hardware setup costs around $130. As in the real world, the magnitude of the sensors will be increased, so that the cost will only reach up to $300 (which is a quite remarkable feat).

3. I have magnificently solved an old-age problem of water management by incorporating about 30 electrical components together and making a project which can be either used by a single person or by the entire community.

4. We have made all the videos and the images for the project on our own. This one is also special because this was an area out of our expertise and we are sure that the videos and the images bring the best out of the project. The hard work of our team rightly reflects in each of the project's components i.e., website, software, hardware configurations, and the actual working of the project.

5. Be it the **serial communication** between Arduino and local-host, sending Twilio messages to the user through the program execution, sending customized-email templates to the user while using the website, accurately capturing the sensors' response to putting it all together to make a project which can serve the humanity, it was a great experience and we are happy that we pulled out a project which is more than just a project.
