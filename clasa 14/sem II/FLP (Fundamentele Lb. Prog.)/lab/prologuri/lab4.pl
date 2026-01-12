:- include('words.pl').

% 1
la_dreapta(X, Y) :- X is Y + 1.
la_stanga(X, Y) :- Y is X + 1.
langa(X, Y) :- la_dreapta(X, Y); la_stanga(X, Y).

solutie(Strada,PosesorZebra) :-
    Strada = [
        casa(1,_,_,_,_,_),
        casa(2,_,_,_,_,_),
        casa(3,_,_,_,_,_),
        casa(4,_,_,_,_,_),
        casa(5,_,_,_,_,_)],
%Englezul locuieste in casa rosie.
member(casa(_,englez,rosie,_,_,_), Strada),
%Spaniolul are un caine.
member(casa(_,spaniol,_,caine,_,_), Strada),
%in casa verde se bea cafea.
member(casa(_,_,verde,_,cafea,_), Strada),
%Ucraineanul bea ceai.
member(casa(_,ucrainean,_,_,ceai,_), Strada),
%Casa verde este imediat in dreapta casei bej.
member(casa(CasaVerde,_,verde,_,_,_), Strada),
member(casa(CasaBej,_,bej,_,_,_), Strada),
la_dreapta(CasaVerde, CasaBej),
%Fumatorul de ”Old Gold” are melci.
member(casa(_,_,_,melci,_,"Old Golds"), Strada),
%in casa galbena se fumeaza ”Kools”.
member(casa(_,_,galbena,_,_,"Kools"), Strada),
%in casa din mjloc se bea lapte.
length(Strada, L),
Mij is div(L, 2) + 1,
member(casa(Mij,_,_,_,lapte,_), Strada),
%Norvegianul locuieste in prima casa.
member(casa(1,norvegian,_,_,_,_), Strada),
%Fumatorul de ”Chesterfields” locuieste langa cel care are o vulpe.
member(casa(CasaChester,_,_,_,_,"Chesterfields"), Strada),
member(casa(CasaVulpe,_,_,vulpe,_,_), Strada),
langa(CasaChester, CasaVulpe),
%”Kools” sunt fumate in casa de langa cea in care se tine calul.
member(casa(CasaKools,_,_,_,_,"Kools"), Strada),
member(casa(CasaCal,_,_,calul,_,_), Strada),
langa(CasaKools, CasaCal),
%Fumatorul de ”Lucky Strike” bea suc de portocale.
member(casa(_,_,_,_,"suc de portocale","Lucky Strike"), Strada),
%Japonezul fumeaza ”Parliaments”.
member(casa(_,japonez,_,_,_,"Parliaments"), Strada),
%Norvegianul locuieste langa casa albastra.
member(casa(CasaNorvegian,norvegian,_,_,_,_), Strada),
member(casa(CasaAlbastra,_,albastra,_,_,_), Strada),
langa(CasaNorvegian, CasaAlbastra),
%posesor zebra
member(casa(_,PosesorZebra,_,zebra,_,_), Strada).

%casa(Numar,Nationalitate,Culoare,AnimalCompanie,Bautura,Tigari)




% 2

word_letters(Word, X) :- atom_chars(Word, X).

cover([], _).
cover([H|L1], L2) :- select(H, L2, Rest),
    cover(L1, Rest).

solution(L1, Word, N) :- word(Word), 
    word_letters(Word, L2), 
    cover(L2, L1), 
    length(L2, N).

%trySolution(_, _, 0) :- false.
trySolution(L, Word, N) :- (solution(L, R, N) -> Word = R ; N1 is N - 1, trySolution(L, Word, N1)).

topsolution(L1, Word) :- length(L1, N), 
    trySolution(L1, Word, N).