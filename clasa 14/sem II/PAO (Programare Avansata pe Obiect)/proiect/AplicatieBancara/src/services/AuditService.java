package services;

import java.io.*;
import java.text.SimpleDateFormat;

public class AuditService {
    private record CsvData(String data){ }
    private static final String folder = "src/utilities/audit";
    private static final String file = "audit.csv";
    private static final String path = folder + "/" + file;
    private static final SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");


    private static void createAuditFile() throws IOException {
        FileWriter writer = new FileWriter(path);
        writer.append("action,timestamp\n");

        writer.flush();
        writer.close();
    }

    //help: https://stackoverflow.com/questions/30073980/java-writing-strings-to-a-csv-file
    public static void writeLogInAudit(String action) throws IOException {

        String timestamp = dateFormat.format(System.currentTimeMillis());
        CsvData data = new CsvData(String.join(",", new String[]{action, timestamp}));

        try (FileWriter fileWriter = new FileWriter(path, true);PrintWriter printWriter = new PrintWriter(fileWriter)){
            printWriter.println(data.data);
        }
        catch (FileNotFoundException e){
            createAuditFile();
            writeLogInAudit(action);
        }
    }
}
