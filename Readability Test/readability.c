#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int compute_letters(string str);
int compute_words(string str);
int compute_sentences(string str);

int main(void)
{
    string s = get_string("string: ");
    int letters = compute_letters(s);
    int words = compute_words(s);
    int sentences = compute_sentences(s);

    //computes the avg number of letters per 100 words
    float L = 100 * ((float)letters / words);
  
    //computes avg number of sentences per 100 words
    float S = 100 * ((float)sentences / words);
  
    float index = 0.0588 * L - 0.296 * S - 15.8;
 
    int grade = round(index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}


int compute_sentences(string str)
{
    int compute_sentences = 0;
    // A sentence ends at either . / ! /?
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (str[i] == '.' || str[i] == '!' || str[i] == '?')
        {
            compute_sentences ++;
        } 
    }
    return compute_sentences;
}


int compute_words(string str)
{
    int compute_words = 1;
    for (int i = 0, n = strlen(str); i < n; i++)
        // A word ends at a space
    {
        if (str[i] == ' ')
        {
            compute_words ++;
        }
    }
    return compute_words;
}


int compute_letters(string str)
{
    int count_letters = 0;
    int n = strlen(str);
    // Calculates number of letters ignoring any other characters
    for (int i = 0; i < n; i++)
    {
        if (isalpha(str[i]) != 0)
        {
            count_letters ++;
        }
    }
    return count_letters;
}

