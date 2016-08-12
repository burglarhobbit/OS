package com.google.engedu.anagrams;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Random;
import java.util.Arrays;
import java.util.HashSet;
import java.util.HashMap;

public class AnagramDictionary {

    private static final int MIN_NUM_ANAGRAMS = 5;
    private static final int DEFAULT_WORD_LENGTH = 3;
    private static final int MAX_WORD_LENGTH = 7;
    private int wordLength = DEFAULT_WORD_LENGTH;
    private Random random = new Random();
    private ArrayList<String> wordList;
    private HashSet<String> wordSet;
    private HashMap<String,ArrayList<String>> lettersToWord;
    private HashMap<Integer,ArrayList<String>> sizeToWords;

    public AnagramDictionary(InputStream wordListStream) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(wordListStream));
        wordList = new ArrayList<String>();
        wordSet = new HashSet<String>();
	lettersToWord = new HashMap<String,ArrayList<String>>();
        sizeToWords = new HashMap<Integer,ArrayList<String>>();
        String line;

        while((line = in.readLine()) != null) {
            String word = line.trim();
            int length = word.length();
            wordList.add(word);
            wordSet.add(word);
            String sortedWord = sortLetters(word);
            
	    // Using HashMap to store the words according to sorted version of words as a key
            lettersToWord.putIfAbsent(sortedWord,new ArrayList<String>());
            lettersToWord.get(sortedWord).add(word);

	    // Using HashMap to store the words according to the length of words as key
            sizeToWords.putIfAbsent(length,new ArrayList<String>());
            sizeToWords.get(length).add(word);
            }
        }

	/* This is an extension where it will remove the words from the list of possible started words
	   if its number of possible anagrams is less than MIN_NUM_ANAGRAMS */
        for(String key: lettersToWord.keySet()) {
            if(lettersToWord.get(key).size() < MIN_NUM_ANAGRAMS) {
		for(String word: lettersToWord.get(key)) {
                    sizeToWords.get(key.length()).remove(word);
                }
            }
        }
    }

    public boolean isGoodWord(String word, String base) {
        return wordSet.contains(word) && !word.contains(base);
    }

    /* The below snippet will return each and every possible anagrams of a given word */
    public ArrayList<String> getAnagrams(String targetWord) {
        ArrayList<String> result = new ArrayList<String>();
        String sortedWord = sortLetters(targetWord);
        /*for(String word: wordList) {
            if(targetWord.length() == word.length()) {
                if(sortedWord.equals(sortLetters(word)) && targetWord.equals(word)!= true) {
                    result.add(word);
                }
            }
        }*/
	result.add(lettersToWord.get(sortedWord));
	result.remove(targetWord);
        return result;
    }

    /* This function will iterate through each alphabets while adding it to the base word and then
       getting the anagrams from the HashMap by using the sorted version of the added word as a key */
    public ArrayList<String> getAnagramsWithOneMoreLetter(String word) {
        ArrayList<String> result = new ArrayList<String>();

        for(char alphabet = 'a'; alphabet <= 'z';alphabet++) {
            result.add(lettersToWord.get(sortLetters(word+alphabet)));
        }
        return result;
    }

    /* This is an extension where the user can play the game by adding two more letters
       to the possible starter word */
    public ArrayList<String> getAnagramsWithTwoMoreLetter(String word) {
        ArrayList<String> result = new ArrayList<String>();

        for(char alphabet = 'a'; alphabet <= 'z';alphabet++) {
            for(char alphabet1 = 'a'; alphabet1 <= 'z';alphabet1++) {
                result.add(lettersToWord.get(sortLetters(word+alphabet+alphabet1)));
        }
        return result;
    }

    /* A good starter word would be picked with the words having default size of wordLength 
       which is incremented as the game progresses */
    public String pickGoodStarterWord() {
        Random rand = new Random();
        
        for(String word: sizeToWords.get(wordLength)) {
            
            if(lettersToWord(sortLetters(word)).size() >= MIN_NUM_ANAGRAMS) {
                if(wordLength < MAX_WORD_LENGTH) {
                    wordLength++;
                }
                return word;
            }
        }
    }

    /* Sorting of a String in alphabetical order and returning the sorted version of the given argument String */
    public String sortLetters(String word) {
        char[] chars = word.toCharArray();
        Arrays.sort(chars);
        String newWord = new String(chars);
        return newWord;
    }
}
