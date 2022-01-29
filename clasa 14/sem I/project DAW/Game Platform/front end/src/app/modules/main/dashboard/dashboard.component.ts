import { Component, OnInit} from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.scss'],
})
export class DashboardComponent implements OnInit {

  constructor(
    private router: Router,
    ) { }

  ngOnInit(): void {
  }

  public navbarSelect(event : any): void{
    switch(event.index){
      case 0:
        this.router.navigate(['/dashboard/home']);
        break;
      case 1:
        this.router.navigate(['/dashboard/games']);
        break;
      case 2:
        this.router.navigate(['/dashboard/companies']);
        break;
      case 3:
        this.router.navigate(['/dashboard/events']);
        break;
    }
  }
}
