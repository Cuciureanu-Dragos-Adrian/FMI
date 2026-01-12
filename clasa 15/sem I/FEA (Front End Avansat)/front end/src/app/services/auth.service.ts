import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class AuthService {

  public url = 'http://localhost:5000/api/Authentication/';

  constructor(
    public http: HttpClient,
  ) { }

  public login(loginForm : any) : Observable<any>{
    return this.http.post(this.url + 'login', loginForm);
  }

  public signup(signupForm : any) : Observable<any>{
    return this.http.post(this.url + 'signupUser', signupForm);
  }

  public generateHeader(): HttpHeaders{
    const token = localStorage.getItem('Role');
    var headers = new HttpHeaders().set('Authorization', 'Bearer ' + token);
    return headers;
  }
}
