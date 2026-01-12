package services;

import java.io.*;
import java.text.SimpleDateFormat;

public class AuditCsvService {

    /** Forces the user to use the convertToCSV function
     *
     */
    private record CsvData(String data){ }
    private static final String csvFolder = "audit";
    private static final String csvFile = "audit.csv";
    private static final String csvPath = csvFolder + "/" + csvFile;
    private static final SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");

    /** Only gets called if the file at csvPath does not exist. Creates the file and names the fields
     *
     */
    private static void createAuditFile() throws IOException {
        var discard = new File(csvFolder).mkdirs(); //create the folder
     FileWriter writer = new FileWriter(csvPath); //creates the file as it does not exist
     writer.append("action-name,timestamp\n");

     writer.flush(); // commit changes
     writer.close(); // close file
   }

    /** Writes given log to a csv file.
     * Inspiration: <a href="https://stackoverflow.com/questions/30073980/java-writing-strings-to-a-csv-file">https://stackoverflow.com/questions/30073980/java-writing-strings-to-a-csv-file</a>
     *
     * @param action - action executed
     */
   public static void writeLogToCsv(String action) throws IOException {

       String timestamp = dateFormat.format(System.currentTimeMillis()); //get current time
       CsvData data = convertToCsvData(new String[]{action, timestamp});

       try (FileWriter fileWriter = new FileWriter(csvPath, true);PrintWriter printWriter = new PrintWriter(fileWriter)){
            printWriter.println(data.data);
       }
       catch (FileNotFoundException e){ //file does not exist
            createAuditFile(); //create file
            writeLogToCsv(action); //try writing to file again
       }
   }

    /** Converts an array of strings to csv format.
     *
     * @param data array of strings to be converted
     * @return formatted csv data
     */
   public static CsvData convertToCsvData(String[] data){
        return new CsvData(String.join(",", data));
   }
}
