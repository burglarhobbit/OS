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
    private Random random = new Random();
    private ArrayList<String> wordList;
    private HashSet<String> wordSet;
    private HashMap<String,ArrayList>;

    public AnagramDictionary(InputStream wordListStream) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(wordListStream));
        wordList = new ArrayList<String>();
        wordSet = new HashSet<String>();
        String line;
        while((line = in.readLine()) != null) {
            String word = line.trim();
            wordList.add(word);
            wordSet.add(word);
        }
    }

    public boolean isGoodWord(String word, String base) {
        return wordSet.contains(word) && !word.contains(base);
    }

    public ArrayList<String> getAnagrams(String targetWord) {
        ArrayList<String> result = new ArrayList<String>();
        String sortedWord = sortLetters(targetWord);
        for(String word: wordList) {
            if (targetWord.length() == word.length()) {
                if (sortedWord.equals(sortLetters(word)) && targetWord.equals(word)!= true) {
                    result.add(word);
                }
            }
        }

        return result;
    }

    public ArrayList<String> getAnagramsWithOneMoreLetter(String word) {
        ArrayList<String> result = new ArrayList<String>();
        String sortedWord = sortLetters(word);

        if (word.length()==pickGoodStarterWord().length()+1 && isGoodWord(word,pickGoodStarterWord())) {
            result.add(word);
        }
        return result;
    }

    public String pickGoodStarterWord() {
        return "stop";
    }

    public String sortLetters(String word) {
        char[] chars = word.toCharArray();
        Arrays.sort(chars);
        String newWord = new String(chars);
        return newWord;
    }
}
