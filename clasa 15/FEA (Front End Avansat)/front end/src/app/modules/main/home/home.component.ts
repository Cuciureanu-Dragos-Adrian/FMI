import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Subscription } from 'rxjs';
import { DataService } from 'src/app/services/data.service';


@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.scss']
})
export class HomeComponent implements OnInit {

  public subscription!: Subscription;
  public loggedUser : any;

  constructor(
    private router: Router,
    private dataService: DataService,
  ) { }

  ngOnInit(): void {
    this.subscription = this.dataService.currentUser.subscribe(user => this.loggedUser = user)
  }

  public logout(): void
  {
    localStorage.setItem('Role', 'Anonymus');
    this.router.navigate(['/login']);
  }
}