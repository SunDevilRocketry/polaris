#version 330 core
    
out vec4 FragColor;

void main()
{
    // rgb colors
    float red = 179;
    float green = 179;
    float blue = 179;
    float alpha = 1.0;

    // convert to normalized paramters
    float redn = red/255.0;
    float greenn = green/255.0;
    float bluen = blue/255.0;

    // set color output
    FragColor = vec4(redn, greenn, bluen, alpha);
}

