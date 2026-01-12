import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class Task3 extends Thread{
    private final String cuv;
    private final String filePath;

    Task3(String cuv, String filePath){
        this.cuv = cuv;
        this.filePath = filePath;
    }

    int determNrAparitii() throws IOException {
        String text = Files.readString(Paths.get(filePath));
        List<String> cuvinte =  List.of(text.split("[,. ;!?\n]+"));

        int nr = 0;

        for (String s : cuvinte) {
            if (cuv.equals(s)) {
                nr++;
            }
        }

        return nr;
    }

    @Override
    public void run(){
        var nr = 0;

        try {
            nr = determNrAparitii();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        System.out.println(nr);
    }
}
