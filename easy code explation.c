// GPIOC, RCC, ও TIM2 এর base address define করা হচ্ছে
#define GPIOC_BASE 0x40011000 
#define RCC_BASE 0x40021000 

// RCC এর APB2 এবং APB1 clock enable register define করা হচ্ছে
#define RCC_APB2ENR (*(volatile unsigned int *) (RCC_BASE + 0x18))
#define RCC_APB1ENR  (*(volatile unsigned int *) (RCC_BASE +0x1C))

// GPIOC এর CRH, BSRR এবং ODR রেজিস্টার define করা হচ্ছে
#define GPIOC_CRH (*(volatile unsigned int *) (GPIOC_BASE +0x04))
#define GPIOC_BSRR (*(volatile unsigned int *) (GPIOC_BASE +0x10))
#define GPIOC_ODR (*(volatile unsigned int *) (GPIOC_BASE + 0x0C))

// Timer2 এর base address ও এর বিভিন্ন রেজিস্টার define করা হচ্ছে
#define TIM2_BASE  0x40000000
#define TIM2_ARR (*(volatile unsigned int *) (TIM2_BASE + 0x2C))  // Auto Reload Register
#define TIM2_CR1 (*(volatile unsigned int *) (TIM2_BASE + 0x00))  // Control Register 1
#define TIM2_SR (*(volatile unsigned int *) (TIM2_BASE + 0x10))   // Status Register
#define TIM2_PSC (*(volatile unsigned int *) (TIM2_BASE + 0x28))  // Prescaler

int main()
{
	// GPIOC এর ঘড়ি চালু করা হচ্ছে (IO port C enable)
	RCC_APB2ENR |= (1u<<4);

	// Timer2 এর ঘড়ি চালু করা হচ্ছে
	RCC_APB1ENR |= (1u<<0);
	
	// GPIOC এর পিন 13 কে output mode এ কনফিগার করার জন্য CRH register আপডেট করা হচ্ছে
	// পিন 13 clear করার জন্য নিচের লাইন
	GPIOC_CRH &= 0xFF0FFFFF;
	// পিন 13 কে General purpose output push-pull হিসেবে সেট করা হচ্ছে
	GPIOC_CRH |= 0x00200000;
	
	// Timer2 এর জন্য Prescaler সেট করা হচ্ছে (PSC = 7999)
	TIM2_PSC = 7999;

	// Auto Reload Register এর মান সেট করা হচ্ছে (ARR = 999)
	TIM2_ARR = 999;

	// Timer চালু করা হচ্ছে
	TIM2_CR1 |= 0x1;
	
	// নিচের কোডটি comment করা আছে, এটি ব্যবহার করলে delay এর মাধ্যমে LED ব্লিংক করা যাবে
	/*
	while(1)
	{
		GPIOC_BSRR  |= (1u <<13);  // পিন 13 high করা
		for (int i=0;i<5000000;i++){}  // কিছু সময় delay
		GPIOC_BSRR  |= (1u <<29);  // পিন 13 low করা (reset bit)
		for (int i=0;i<5000000;i++){}  // কিছু সময় delay
	}
	*/
	
	// Timer এর update event অনুযায়ী পিন 13 toggle করার জন্য লুপ
	while(1)
	{
		// Timer2 এর update flag check করা হচ্ছে
		if(TIM2_SR & (1u<<0))
		{
			// Update flag clear করা হচ্ছে
			TIM2_SR &= ~(1u<<0);
			
			// GPIOC এর পিন 13 এর অবস্থা toggle করা হচ্ছে (high <-> low)
			GPIOC_ODR ^= (1u<<13);
		}
		
	}
}
