import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { AuthService } from './auth.service';

@Injectable({
  providedIn: 'root'
})
export class CompaniesService {

  public url = 'https://localhost:5001/api/Company/';

  constructor(
    public http: HttpClient,
    private authService : AuthService,
  ) { }

  //getters
  public getCompanies(): Observable<any>{
    return this.http.get(`${this.url}companies`, {headers : this.authService.generateHeader()});
  }

  public getCompanyById(id : any): Observable<any>{
    return this.http.get(`${this.url}filterById/${id}`, {headers : this.authService.generateHeader()});
  }

  public addCompany(company: any): Observable<any>{
    return this.http.post(`${this.url}companyAndHeadquarter`, company, {headers : this.authService.generateHeader()});
  }

  public editCompany(company: any): Observable<any>{
    return this.http.put(`${this.url}companyAndHeadquarter`, company, {headers : this.authService.generateHeader()});
  }

  public deleteCompany(company: any): Observable<any>{
    return this.http.delete(`${this.url}companyAndHeadquarter${company.id}`, {headers : this.authService.generateHeader()});
  }
}
