import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { CompaniesComponent } from './companies/companies.component';
import { CompanyComponent } from './company/company.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { EventsComponent } from './events/events.component';
import { GamesComponent } from './games/games.component';
import { HomeComponent } from './home/home.component';

const routes: Routes = [
    {
      path: 'dashboard',
      component: DashboardComponent,
    
      children: [
      {
        path: '',
        redirectTo: 'home',
      },
      {
        path: 'home',
        component: HomeComponent,
      },
      {
        path: 'games',
        component: GamesComponent
      },
      {
        path: 'companies',
        component: CompaniesComponent,
      },
      {
        path: 'events',
        component: EventsComponent,
      },
      {
        path: '**',
        redirectTo: 'home',
      }]
    },
    {
      path: 'company/:id',
      component: CompanyComponent,
    },
    // {
    //   path: '**',
    //   redirectTo: 'dashboard'
    // }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class MainRoutingModule { }
