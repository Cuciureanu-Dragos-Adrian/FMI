import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class Examen2017Sept {
    public static void main(String[] args) {
        task2();
    }

    public static void task2(){
        List<Vacanta> vacante = List.of(
                new Vacanta("Aloha", 2, Float.parseFloat("3.3"), "12-13"),
                new Vacanta("Konoha", 2, Float.parseFloat("3.323"), "12-13"),
                new Vacanta("Aloha", 2, Float.parseFloat("3232.3"), "12-13"),
                new Vacanta("Dubai", 23, Float.parseFloat("3.3232"), "14-17"),
                new Vacanta("Dubai", 23, Float.parseFloat("3.3"), "12-13"),
                new Vacanta("Aloha", 23, Float.parseFloat("3.3"), "12-13")
        );

        Examen2017SeptTask2.a(vacante);
        Examen2017SeptTask2.b(vacante);
        System.out.println(Examen2017SeptTask2.c(vacante));
        Examen2017SeptTask2.d(vacante);
    }
}


class Vacanta{
    String destinatie;
    int nr_persoane;
    float valoare;
    String perioada;

    public Vacanta(String destinatie, int nr_persoane, float valoare, String perioada) {
        this.destinatie = destinatie;
        this.nr_persoane = nr_persoane;
        this.valoare = valoare;
        this.perioada = perioada;
    }


    public String getDestinatie() {
        return destinatie;
    }

    public int getNr_persoane() {
        return nr_persoane;
    }

    public float getValoare() {
        return valoare;
    }

    public String getPerioada() {
        return perioada;
    }


    public void setDestinatie(String destinatie) {
        this.destinatie = destinatie;
    }

    public void setNr_persoane(int nr_persoane) {
        this.nr_persoane = nr_persoane;
    }

    public void setValoare(float valoare) {
        this.valoare = valoare;
    }

    public void setPerioada(String perioada) {
        this.perioada = perioada;
    }


    @Override
    public String toString() {
        return "Vacanta{" +
                "destinatie='" + destinatie + '\'' +
                ", nr_persoane=" + nr_persoane +
                ", valoare=" + valoare +
                ", perioada='" + perioada + '\'' +
                '}';
    }
}

class Examen2017SeptTask2{

    static void a(List<Vacanta> list){
        list.stream()
                .filter(x -> x.getNr_persoane() == 2)
                .sorted(Comparator.comparing(Vacanta::getValoare).reversed())
                .forEach(System.out::println);
    }

    static void b(List<Vacanta> list){
        list.stream()
                .map(Vacanta::getDestinatie)
                .distinct()
                .forEach(System.out::println);
    }

    static List<Vacanta> c(List<Vacanta> list){
        return list.stream()
                .filter(x -> x.getDestinatie().equals("Dubai") && x.getPerioada().contains("14-"))
                .toList();
    }

    static void d(List<Vacanta> list){
        list.stream()
                .collect(Collectors.groupingBy(Vacanta::getDestinatie))
                .entrySet()
                .forEach(System.out::println);
    }
}