package io;
/**
 * FileParser class.
 * Writes output to files and reads input from files
 *
 * @author Luke Tran, Sean Caldwell, Calvin Lapp
 * @since March 15th, 2020
 * @version 1.0
 * @name FileParser.java
 */

import java.util.Vector;
import java.io.File;
import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class FileParser {

    private FileParser() {
        // don't allow instantiation 
    }

    /* Methods */

    /**
    * Write new data to the specified data
    * @param data
    * @return
    */
    public static void writeFile(String file, Vector<String> data) {

        //write details to the current file
        try {
              PrintWriter pw = new PrintWriter(file);
              for(int i = 0; i < data.size(); i++){
                  pw.println(data.get(i));
              }
              pw.flush();
              pw.close();
          } catch (FileNotFoundException fnfe){
              System.out.println(fnfe);
          }
      }


    /**
     * Retrieve all data from a file, one line at a time.
     * Store these lines in a vector. 
     * @param fileName
     * @return a vector containing all of the lines of a file.
     */
    public static Vector<String> getFileInfo(String fileName) {
        Vector<String> data = new Vector<String>();
        try {
            File file = new File(fileName);
            Scanner reader = new Scanner(file);
            while(reader.hasNext()){
                
                String line = reader.nextLine();
                if (!line.substring(0, 3).equals("END")) {
                    data.add(line);
                }
            }
            reader.close();
        }catch(FileNotFoundException e) {
            System.out.println("An error occured.");
            e.printStackTrace();
        }
        return data;
    }
}