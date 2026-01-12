import java.util.*;
import java.util.stream.Collectors;


class Automobil {
    String marca;
    String model;
    int capacitate;
    int pret;

    Automobil(String marca, String model, int capacitate, int pret){
        this.marca = marca;
        this.model = model;
        this.capacitate = capacitate;
        this.pret = pret;
    }


    int getPret(){
        return pret;
    }

    public String getMarca() {
        return marca;
    }

    public String getModel() {
        return model;
    }

    public int getCapacitate() {
        return capacitate;
    }

    public void setMarca(String marca) {
        this.marca = marca;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public void setCapacitate(int capacitate) {
        this.capacitate = capacitate;
    }

    public void setPret(int pret) {
        this.pret = pret;
    }


    @Override
    public String toString() {
        return String.format("marca: %s \nmodel: %s \ncapacitate: %d \npret: %d \n", marca, model, capacitate, pret);
    }


    public boolean equals(Automobil a) {
        return Objects.equals(a.marca, marca) && Objects.equals(a.model, model) && a.capacitate == capacitate && a.pret == pret;
    }
}



class Task2{
    public static List<Automobil> automobilsOver500Desc(List<Automobil> automobils){
        return automobils.stream()
                .filter(x -> x.pret >= 5000)
                .sorted(Comparator.comparing(Automobil::getPret).reversed())
                .toList();
    }

    public static List<String> distinctMarci(List<Automobil> automobils){
        return automobils.stream()
                .map(Automobil::getMarca)
                .distinct()
                .toList();
    }

    public static List<Automobil> capac20003000(List<Automobil> automobils){
        return automobils.stream()
                .filter(x -> x.capacitate >= 2000 && x.capacitate <= 3000)
                .toList();
    }

    public static Map<String, List<String>> marcaModele(List<Automobil> automobils){
        return automobils.stream()
                .collect(Collectors.groupingBy(Automobil::getMarca))
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, x -> x.getValue().stream().map(Automobil::getModel).distinct().toList()));
    }

    public static Map<String, Set<String>> modelsForEachBrand(List<Automobil> list) {
        return list
                .stream()
                .filter(x -> x.getCapacitate() >= 3000)
                .collect(Collectors.groupingBy(Automobil::getMarca,
                        Collectors.mapping(Automobil::getModel, Collectors.toSet())));
    }

    public static Map<String, List<String>> marcaModeleBun(List<Automobil> list){
        return list
                .stream()
                .collect(Collectors.groupingBy(Automobil::getMarca, Collectors.collectingAndThen(
                        Collectors.toList(), x -> x.stream()
                                .sorted(Comparator.comparing(Automobil::getPret).reversed())
                                .map(Automobil::getModel)
                                .distinct()
                                .limit(2)
                                .toList())));
    }

    public static Map<String, List<String>> marcaModeleBun2(List<Automobil> list){
        return list
                .stream()
                .filter(x -> x.getMarca().equals("dacia"))
                .collect(Collectors.groupingBy(Automobil::getMarca, Collectors.collectingAndThen(
                        Collectors.toList(), x -> x.stream()
                                .map(Automobil::getModel)
                                .distinct()
                                .toList())));
    }

    public static void marcaModeleBun3(List<Automobil> list){
        list.stream()
                .collect(Collectors.groupingBy(Automobil::getMarca, Collectors.collectingAndThen(
                        Collectors.toList(), x -> x.stream()
                                .map(Automobil::getModel)
                                .distinct()
                                .toList())))
                .entrySet()
                .forEach(System.out::println);
    }
}
