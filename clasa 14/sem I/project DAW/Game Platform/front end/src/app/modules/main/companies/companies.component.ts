import { Component, OnInit } from '@angular/core';
import { MatDialog, MatDialogConfig } from '@angular/material/dialog';

import { Router } from '@angular/router';
import { Subscription } from 'rxjs';
import { CompaniesService } from 'src/app/services/companies.service';
import { DataService } from 'src/app/services/data.service';
import { AddEditCompanyComponent } from '../../shared/add-edit-company/add-edit-company.component';

@Component({
  selector: 'app-companies',
  templateUrl: './companies.component.html',
  styleUrls: ['./companies.component.scss']
})
export class CompaniesComponent implements OnInit {

  public subscription!: Subscription;
  public loggedUser : any;
  public companies: any = [];

  constructor(
    private router: Router,
    private dataService: DataService,
    private companiesService: CompaniesService,
    public dialog: MatDialog,
    ) { }

  ngOnInit(): void {
    this.subscription = this.dataService.currentUser.subscribe(user => this.loggedUser = user)
      this.companiesService.getCompanies().subscribe({
      next:(result : any) => {
        this.companies = result;
      },
      error:(error : any) => {
        console.error(error);
      },
    })
  }

  public openModal(company? : any): void {
    const data = {
      company
    }
    const dialogConfig = new MatDialogConfig();
    dialogConfig.width = '300px';
    dialogConfig.height = '200px';
    dialogConfig.data = data;

    const dialogRef = this.dialog.open(AddEditCompanyComponent, dialogConfig);
    dialogRef.afterClosed().subscribe({
      next:(result) => {
        if(result){
          this.companies = result;
        }
      },
      error:(error) => {
        console.log(error);
      }
    })
  }

  public addNewCompany(): void{
    this.openModal();
  }

  public editCompany(company : any): void{
    this.openModal(company);
  }

  public deleteCompany(company : any): void{
    this.companiesService.deleteCompany(company).subscribe({
      next:(result) =>{
        this.companies = result;
      },
      error:(error) => {
        console.log(error);
      }
    })
  }

  ngOnDestroy(): void {
      this.subscription.unsubscribe();
  }

  public logout(): void
  {
    localStorage.setItem('Role', 'Anonymus');
    this.router.navigate(['/login']);
  }
}
