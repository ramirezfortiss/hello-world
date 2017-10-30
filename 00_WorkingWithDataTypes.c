
#include <assert.h>
#include "open62541.h"
#include <stdio.h>
#include <open62541.h>

/**
 * UA_Variants is a sort of container where you place one data type and a pointer to that data type
*/
static void myNewTestBranch_form_Terminal(void){
	printf("a new github-branch was created!\n");
}

static void
variables_variants(void) {
    /* Set a scalar value */
	/* Set the variant to a scalar value that already resides in memory. The value
 	* takes on the lifecycle of the variant and is deleted with it.
 	*
	* @param v The variant
	* @param p A pointer to the value data
	* @param type The datatype of the value in question */

    UA_Variant v;
    UA_Int32 i = 42;
    UA_Variant_setScalar(&v, &i, &UA_TYPES[UA_TYPES_INT32]);

        printf("The initial int value is \t\t i = %d, \tits address is \t&i = %p \n",i, &i);
//        printf("The variant v is now type int. \t v = %d \n", v.data); // option 1, i is value input in UA_variant_setScalar(...)
        printf("The variant v has \t v.data = %p \n", v.data); // OPTION 2, i is address input in UA_variant_setScalar(...)
        printf("\n");
    /* Make a copy */
    UA_Variant v2;
    UA_Variant_copy(&v, &v2);
        printf("The variant v2 has \t v.data = %p \n", v2.data);
        printf("\n");
    UA_Variant_deleteMembers(&v2);
        printf("The variant v2 after deleteMembers has \t v2.data = %p \n", v2.data);
        printf("\n");

    /* Set an array value */
	/* Set the variant to an array that already resides in memory. The array takes
	 * on the lifecycle of the variant and is deleted with it.
	 *
	 * @param v The variant
	 * @param array A pointer to the array data
	 * @param arraySize The size of the array
	 * @param type The datatype of the array */
    UA_Variant v3;
    UA_Double d[9] = {1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0};
    
    printf("Array d hast the addresses:\t%p \t%p \n", &d[0], &d[8]);

    UA_Variant_setArrayCopy(&v3, d, 9, &UA_TYPES[UA_TYPES_DOUBLE]);
//    printf("\nThe variant v3 has \t v3.data = %p \n", v3.data);


    /* Set array dimensions */
    v3.arrayDimensions = (UA_UInt32 *)UA_Array_new(2, &UA_TYPES[UA_TYPES_UINT32]);
    v3.arrayDimensionsSize = 2;
    v3.arrayDimensions[0] = 3;
    v3.arrayDimensions[1] = 3;
    UA_Variant_deleteMembers(&v3);
}

static void
variables_nodeids(void) {
    UA_NodeId id1 = UA_NODEID_NUMERIC(1, 1234); /* shorthand for creating a numeric-type NodeIds. NamespaceIndex = 1,  */
    id1.namespaceIndex = 3;

    UA_NodeId id2 = UA_NODEID_STRING(1, "testid"); /* the string is static */
    UA_Boolean eq = UA_NodeId_equal(&id1, &id2);
    if(eq)
        return;

    UA_NodeId id3;
    UA_NodeId_copy(&id2, &id3);
    UA_NodeId_deleteMembers(&id3);

    UA_NodeId id4 = UA_NODEID_STRING_ALLOC(1, "testid"); /* the string is copied
                                                            to the heap */
    UA_NodeId_deleteMembers(&id4);
}


static void variables_basic(void){
/*******************************************************************************************/
    printf("\nIntegers:\n");
    UA_Int32 i = 22;
    UA_Int32 j;
//   j = UA_Int32_init()
    UA_Int32_copy(&i, &j);

    UA_Int32 *ip = UA_Int32_new();
    UA_Int32_copy(&i, ip);
//    UA_Int32 *ip = &i;

    printf("ip points to value:\t %d \n",  *ip);
    printf("The value of pointer ip is:\t\t %p \n",  (void *)ip);
    printf("The address of pointer ip is:\t %p \n", (void *) &ip);
    printf("\n");
    printf("The address of i is:\t\t\t %p \n", (void *)&i);
    printf("\n");

    UA_Int32_delete(ip);
//    *ip = NULL;

    printf("ip points to value:\t %d \n",  *ip);
    printf("The value of pointer ip is:\t\t %p \n", (void *) ip);
    printf("The address of pointer ip is:\t %p \n", (void *) &ip);
    printf("\n");
    printf("The address of i is:\t\t\t %p \n", (void *)&i);
    printf("The value of UA_INT i is: %d\n", i);
    printf("\n");

/*******************************************************************************************/
    printf("\nStrings:\n");
    UA_String s;
    UA_String_init(&s);  /*_init zeroes out the entire memory of the datatype*/

    char *test = "casa1";

        printf("this is the char test:\t %s \n", test);
        printf("\n");

    s.length = strlen(test);
    s.data = (UA_Byte*)test;

        printf("this lenght of UA_String s:\t %lu \n", s.length); // s.lenght is from type long unsigned int
        printf("this data of UA_String s:\t %s \n", s.data);
        printf("\n");

    UA_String s2;
    UA_String_copy(&s, &s2);
//    UA_String_deleteMembers(&s2); /* Copying heap-allocated the dynamic content*/

        printf("this lenght of UA_String s2:\t %lu \n", s2.length); // s.lenght is from type long unsigned int
        printf("this data of UA_String s2:\t %s \n", s2.data);
        printf("\n");

    UA_String s3 = UA_STRING("casa1");

        printf("this lenght of UA_String s3:\t %lu \n", s3.length); // s.lenght is from type long unsigned int
        printf("this data of UA_String s3:\t %s \n", s3.data);
        printf("\n");

    UA_String s4 = UA_STRING_ALLOC("casa1"); /* Copies the content to the heap*/
        printf("this lenght of UA_String s4:\t %lu \n", s4.length); // s.lenght is from type long unsigned int
        printf("this data of UA_String s4:\t %s \n", s4.data);
        printf("\n");

    UA_Boolean eq = UA_String_equal(&s2, &s4);
    UA_String_deleteMembers(&s4);

        printf("Do s2 and s4 contain the same number of elements? (eq value):\t %d", eq);

    if(!eq)
        return;

/*******************************************************************************************/
    printf("\nStructured Types:\n");

    UA_CallRequest cr;
    UA_init(&cr, &UA_TYPES[UA_TYPES_CALLREQUEST]); /* Generic method. UA_TYPES_CALLREQUEST = 55 */
    UA_CallRequest_init(&cr); /* Shorthand for the previous line */

    cr.requestHeader.timestamp = UA_DateTime_now(); /* Members of a structure */

    cr.methodsToCall = (UA_CallMethodRequest *)UA_Array_new(5, &UA_TYPES[UA_TYPES_CALLMETHODREQUEST]); /* UA_TYPES_CALLMETHODREQUEST = 45*/
    cr.methodsToCallSize = 5; /* Array size needs to be made known */

    UA_CallRequest *cr2 = UA_CallRequest_new();
    UA_copy(&cr, cr2, &UA_TYPES[UA_TYPES_CALLREQUEST]);

    UA_CallRequest_deleteMembers(&cr);
    UA_CallRequest_delete(cr2);

}

 int main(void){
//     variables_basic();
//     variables_nodeids();
     variables_variants();
     return 0;
 }
