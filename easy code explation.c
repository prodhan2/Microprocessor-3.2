#define RCC_BASE  0x40021000
#define RCC_APB2ENR (*(volatile unsigned int *) (RCC_BASE + 0x18)) // APB2 বাসে ঘড়ি চালু করার রেজিস্টার
#define GPIOC_BASE 0x40011000
#define GPIOC_CRH  (*(volatile unsigned int *) (GPIOC_BASE + 0x04)) // পোর্ট C এর কনফিগারেশন রেজিস্টার (পিন 8-15)
#define GPIOC_ODR  (*(volatile unsigned int *) (GPIOC_BASE + 0x18)) // পোর্ট C এর আউটপুট ডেটা রেজিস্টার

#define RCC_APB1ENR (*(volatile unsigned int *) (RCC_BASE + 0x1C)) // APB1 বাসে ঘড়ি চালু করার রেজিস্টার

#define TIM2_BASE  0x40000000
#define TIM2_SR (*(volatile unsigned int *) (TIM2_BASE + 0x10)) // স্ট্যাটাস রেজিস্টার (UIF bit চেক করতে)
#define TIM2_ARR  (*(volatile unsigned int *) (TIM2_BASE + 0x2C)) // অটো-রিলোড রেজিস্টার (টাইমার কখন রিসেট হবে)
#define TIM2_CR1 (*(volatile unsigned int *) (TIM2_BASE + 0x00)) // কন্ট্রোল রেজিস্টার ১ (টাইমার চালু করতে)
#define TIM2_PSC (*(volatile unsigned int *) (TIM2_BASE + 0x24)) // প্রিস্কেলার রেজিস্টার (টাইমার কতটা ধীরে চলবে তা নির্ধারণ করে)

#define delay  10000

int main()
{
    // পোর্ট C এর জন্য ক্লক চালু করি (bit 4 set করি)
    RCC_APB2ENR |= (1U << 4);

    // Timer 2 এর জন্য ক্লক চালু করি (bit 0 set করি)
    RCC_APB1ENR |= (1U << 0);

    // Prescaler 7999 দিলে মূল ক্লক (8MHz) ভাগ হয়ে হয় 1000 Hz বা প্রতি 1ms তে কাউন্ট বাড়বে
    TIM2_PSC = 7999;

    // Auto Reload Register 999 দিলে প্রতি 1000ms = 1s পর UIF bit set হবে
    TIM2_ARR = 999;

    // পোর্ট C এর পিন 13 কে output হিসেবে সেট করার জন্য CRH রেজিস্টার আপডেট করি
    GPIOC_CRH &= 0xFF0FFFFF;   // পুরাতন কনফিগারেশন ক্লিয়ার করি (bit 20-23)
    GPIOC_CRH |= 0x00200000;   // MODE = 10 (Output 2MHz), CNF = 00 (General purpose push-pull)

    // Timer চালু করি (Counter Enable bit সেট করি)
    TIM2_CR1 |= 1; // CEN bit (bit 0) = 1

    while (1)
    {
        // যদি UIF (Update Interrupt Flag) সেট হয়
        if (TIM2_SR & (1U << 0))
        {
            TIM2_SR &= ~(1U << 0);     // UIF ফ্ল্যাগ ক্লিয়ার করি (নতুন কাউন্টের জন্য)
            GPIOC_ODR ^= (1U << 13);   // পিন 13 টগল করি (ON থাকলে OFF, OFF থাকলে ON)
        }
    }

    // নিচের অংশে টাইমার ব্যবহার না করে সফটওয়্যার ডিলে দিয়ে LED জ্বালানো-বন্ধ করার পদ্ধতি

    /*
    while(1)
    {
        // পিন 13 অন (LED জ্বলে উঠবে)
        GPIOC_ODR |= (1U << 13);

        // কিছু সময় অপেক্ষা (সফটওয়্যার ডিলে)
        for (int i = 0; i < delay; i++) {}

        // পিন 13 বন্ধ (LED নিভে যাবে)
        GPIOC_ODR &= ~(1U << 13);
    }
    */

    return 0;
}
