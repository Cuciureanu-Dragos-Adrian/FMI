import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { AuthService } from './auth.service';

@Injectable({
  providedIn: 'root'
})
export class GamesService {

  public url = 'https://localhost:5001/api/Game/';

  constructor(
    public http: HttpClient,
    private authService : AuthService,
  ) { }

  //getters
  public getGames(): Observable<any>{
    console.log()
    return this.http.get(`${this.url}` + `fullGamesJoined`, {headers : this.authService.generateHeader()});
  }
  public getGamesAlphabeticalAscending(): Observable<any>{
    return this.http.get(`${this.url}` + `filterByAlphabeticalAscending`, {headers : this.authService.generateHeader()});
  }
  public getGamesAlphabeticalDescending(): Observable<any>{
    return this.http.get(`${this.url}` + `filterByAlphabeticalDescending`, {headers : this.authService.generateHeader()});
  }
  public getGamesReviewAscending(): Observable<any>{
    return this.http.get(`${this.url}` + `filterByReviewAscending`, {headers : this.authService.generateHeader()});
  }
  public getGamesReviewDescending(): Observable<any>{
    return this.http.get(`${this.url}` + `filterByReviewDescending`, {headers : this.authService.generateHeader()});
  }

  public addGame(game: any): Observable<any>{
    return this.http.post(`${this.url}justGame`, game, {headers : this.authService.generateHeader()});
  }

  public editGame(game: any): Observable<any>{
    return this.http.put(`${this.url}justGame`, game, {headers : this.authService.generateHeader()});
  }

  public deleteGame(game: any): Observable<any>{
    return this.http.delete(`${this.url}${game.id}`, {headers : this.authService.generateHeader()});
  }
}
