import { Injectable } from '@angular/core';
import { BehaviorSubject } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class DataService {

  private userSource = new BehaviorSubject({
    username: '',
    password: '',
  })

  public currentUser = this.userSource.asObservable();

  constructor() { }

  public changeUserData(user : any): void{
    this.userSource.next(user);
  }
}
