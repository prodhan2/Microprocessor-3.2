নিচে প্রতিটি রেজিস্টারের কাজ বাংলায় ব্যাখ্যা করা হলো:

---

### ✅ `#define RCC_BASE 0x40021000`

**ব্যাখ্যা**:
RCC (Reset and Clock Control) এর বেস ঠিকানা। এই ঠিকানা থেকে RCC এর বিভিন্ন রেজিস্টারে অ্যাক্সেস করা যায়।

---

### ✅ `#define RCC_APB2ENR (*(volatile unsigned int *) (RCC_BASE+0x18))`

**ব্যাখ্যা**:
`RCC_APB2ENR` হল APB2 বাসে সংযুক্ত পেরিফেরালগুলোর ক্লক এনাবল রেজিস্টার।
এটি ব্যবহার করে GPIO, AFIO ইত্যাদি মডিউলের ক্লক চালু/বন্ধ করা যায়।
**যেমন:** `RCC_APB2ENR |= (1 << 4);` → GPIOC-এর ক্লক চালু করে।

---

### ✅ `#define GPIOC_BASE 0x40011000`

**ব্যাখ্যা**:
GPIOC (General Purpose Input Output Port C)-এর বেস ঠিকানা। GPIOC এর রেজিস্টারগুলো এই ঠিকানা থেকে অফসেট দিয়ে নির্ধারিত হয়।

---

### ✅ `#define GPIOC_CRH (*(volatile unsigned int *) (GPIOC_BASE+0x04))`

**ব্যাখ্যা**:
`GPIOC_CRH` হল GPIOC-এর উচ্চ (High) ৮টি পিন (pin 8-15) কনফিগার করার কন্ট্রোল রেজিস্টার।
এখানে প্রতিটি পিনের মোড (ইনপুট/আউটপুট) এবং কনফিগারেশন নির্ধারণ করা হয়।

---

### ✅ `#define GPIOC_ODR (*(volatile unsigned int *) (GPIOC_BASE+0x18))`

**ব্যাখ্যা**:
`GPIOC_ODR` (Output Data Register) দ্বারা GPIOC পোর্টের আউটপুট পিনে ডেটা পাঠানো হয়।
যেমন: `GPIOC_ODR |= (1 << 13);` → পিন 13 হাই করা হয়।

---

### ✅ `#define RCC_APB1ENR (*(volatile unsigned int *) (RCC_BASE+ 0x1C))`

**ব্যাখ্যা**:
`RCC_APB1ENR` হল APB1 বাসের পেরিফেরালগুলোর ক্লক এনাবল রেজিস্টার।
যেমন: Timer2 চালু করতে `RCC_APB1ENR |= (1 << 0);` ব্যবহার করা হয়।

---

### ✅ `#define TIM2_BASE 0x40000000`

**ব্যাখ্যা**:
Timer 2 এর বেস ঠিকানা। এই ঠিকানা থেকে Timer 2 এর বিভিন্ন রেজিস্টার ব্যবহৃত হয়।

---

### ✅ `#define TIM2_SR (*(volatile unsigned int *) (TIM2_BASE + 0x10))`

**ব্যাখ্যা**:
`TIM2_SR` (Status Register) দ্বারা Timer2-এর স্ট্যাটাস জানা যায়।
যেমন: `UIF` ফ্ল্যাগ দিয়ে বোঝা যায় টাইমার ওভারফ্লো হয়েছে কিনা।

---

### ✅ `#define TIM2_ARR (*(volatile unsigned int *) (TIM2_BASE + 0x2C))`

**ব্যাখ্যা**:
`TIM2_ARR` (Auto Reload Register) এ টাইমার কাউন্ট শেষ হলে পুনরায় যেখান থেকে শুরু করবে সেই মান সেট করা হয়।
যেমন: `TIM2_ARR = 1000;` দিলে টাইমার ০ থেকে ১০০০ পর্যন্ত কাউন্ট করে।

---

### ✅ `#define TIM2_CR1 (*(volatile unsigned int *) (TIM2_BASE + 0x00))`

**ব্যাখ্যা**:
`TIM2_CR1` (Control Register 1) দ্বারা Timer2 শুরু/বন্ধসহ বিভিন্ন কনফিগারেশন করা হয়।
যেমন: `TIM2_CR1 |= 1;` → টাইমার চালু করা হয়।

---

### ✅ `#define TIM2_PSC (*(volatile unsigned int *) (TIM2_BASE + 0x24))`

**ব্যাখ্যা**:
`TIM2_PSC` (Prescaler Register) দ্বারা টাইমারের ইনপুট ক্লক ভাগ করা হয়।
যেমন: `TIM2_PSC = 7999;` হলে ইনপুট ক্লক ৮০০০ দিয়ে ভাগ হবে, ফলে টাইমার স্লো হবে।

---

প্রয়োজনে এই কোডের উপরে ভিত্তি করে সম্পূর্ণ প্রোগ্রাম বা কনফিগারেশনেও সাহায্য করতে পারি।
