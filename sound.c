// Plays the pause sound.
void pauseSound(int paused)
{
    int length = 50;

    NR10_REG = 0x00; 
    NR11_REG = 0x80;

    if (paused == 0) // Pause sound
    {
        // C
        NR12_REG = 0x43;  
        NR13_REG = 0x06;
        NR14_REG = 0x87;    
        delay(length);

        // E
        NR12_REG = 0x43;  
        NR13_REG = 0x39;
        NR14_REG = 0x87;  
        delay(length);

        // G
        NR12_REG = 0x43;  
        NR13_REG = 0x59;
        NR14_REG = 0x87;  
        delay(length);

        // High C
        NR12_REG = 0x43;  
        NR13_REG = 0x82;
        NR14_REG = 0x87;  
        delay(length);
    }
    else // Unpause sound
    {
        // High C
        NR12_REG = 0x43;  
        NR13_REG = 0x82;
        NR14_REG = 0x87;  
        delay(length);

        // G
        NR12_REG = 0x43;  
        NR13_REG = 0x59;
        NR14_REG = 0x87;  
        delay(length);

        // E
        NR12_REG = 0x43;  
        NR13_REG = 0x39;
        NR14_REG = 0x87;  
        delay(length);

        // C
        NR12_REG = 0x43;  
        NR13_REG = 0x06;
        NR14_REG = 0x87;    
        delay(length);
    }
}